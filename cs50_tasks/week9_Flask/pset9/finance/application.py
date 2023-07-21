import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    tables = db.execute("SELECT * FROM pocket WHERE user_id = ?", session["user_id"])
    total = float(0.00)
    for table in tables:
        table["price"] = lookup(table["symbol"])["price"]
        table["TOTAL"] = round(float(table["price"]) * float(table["shares"]), 2)
        total = table["TOTAL"] + total
        table["price"] = usd(table["price"])
        table["TOTAL"] = usd(table["TOTAL"])

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = float(cash[0]["cash"])
    total = total + cash
    #cash=usd(cash)
    #total=usd(total)
    return render_template("index.html", tables=tables, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "GET":
        return render_template("buy.html")

    else:
        # get and choose symbol
        symbol = request.form.get("symbol")
        value = lookup(symbol)
        if not symbol or not value:
            return apology("symbol is not correct")
        name = value["name"]

        # get and check shares
        shares = request.form.get("shares")
        if not shares or not shares.isnumeric():
            return apology("Shares isn't correct")
        shares = float(shares)
        if shares <= 0 or (shares - int(shares)) != 0:
            return apology("shares isn't correct")

        # get price & check if we can by so much shares
        price = float(value["price"])
        cost = float(shares)*price
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = float(cash[0]["cash"])
        if cost > cash:
            return apology("You have no so much money((")

        # update cash
        cash = cash - cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        # check if shares is into pocket and update it
        newShares = db.execute("SELECT shares FROM pocket WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        if not newShares:
            db.execute("INSERT INTO pocket (user_id , symbol, name, shares) VALUES(?, ?, ?, ?)",
                       session["user_id"], symbol, name, shares)
        else:
            newShares = int(newShares[0]["shares"]) + int(shares)
            db.execute("UPDATE pocket SET shares = ? WHERE user_id = ? AND symbol = ?", newShares, session["user_id"], symbol)

        # when it's ok turn to index and add to history
        db.execute("INSERT INTO history (user_id, symbol, name, shares, price, time) VALUES(?, ?, ?, ?, ?, DATETIME())",
                   session["user_id"], symbol, name, shares, price)

        return redirect("/")
    """Buy shares of stock"""


@app.route("/history")
@login_required
def history():
    history = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    for event in history:
        event["price"] = usd(event["price"])
    return render_template("history.html", history=history)
    """Show history of transactions"""


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        symbol = lookup(symbol)
        if not symbol:
            return apology("symbol is not correct")

        symbol["price"] = usd(symbol["price"])

        return render_template("quote.html", symbol=symbol)

#    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    if request.method == "POST":

        name = request.form.get("username")
        if not name:
            return apology("Name can't be empty!")
        name_check = db.execute("SELECT username FROM users WHERE username = ?", (name,))
        if len(name_check) != 0:
            return apology("Sorry that username is not allowed")

        password = request.form.get("password")
        if not password:
            return apology("Password can't be empty!")
        if password != request.form.get("confirmation"):
            return apology("passwords do not much")

        db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", name, generate_password_hash(password))

        return redirect("/login")

#    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Take all symbol of user table
    # make get method
    if request.method == "GET":
        symbols = db.execute("SELECT symbol FROM pocket WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", symbols=symbols)

    # make post method
    else:
        # get variables
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Invalid Symbol")

        # get and check shares
        shares = request.form.get("shares")
        if not shares or not shares.isnumeric():
            return apology("Shares isn't correct")
        shares = float(shares)
        if (shares - int(shares)) != 0:
            return apology("shares isn't correct")

        db_shares = db.execute("SELECT shares FROM pocket WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        db_shares = int(db_shares[0]["shares"])
        if db_shares < shares:
            return apology("you haven't so much shares")

        # sell logic

        db_shares = db_shares - shares
        look = lookup(symbol)
        price = float(look["price"])
        name = look["name"]
        cost = float(shares * price)

        if db_shares == 0:
            db.execute("DELETE FROM pocket WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        else:
            db.execute("UPDATE pocket SET shares = ? WHERE user_id = ? AND symbol = ?", db_shares, session["user_id"], symbol)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = float(cash[0]["cash"])
        cash = cash + cost
        db.execute("UPDATE users SET cash = ? WHERE id =?", cash, session["user_id"])
        db.execute("INSERT INTO history (user_id, symbol, name, shares, price, time) VALUES(?, ?, ?, ?, ?, DATETIME())",
                   session["user_id"], symbol, name, -shares, price)
        return redirect("/")


@app.route("/settings", methods=["GET", "POST"])
def settings():
    """Settings user"""
    if request.method == "GET":
        return render_template("settings.html")
    if request.method == "POST":

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure username exists and password is correct
        if not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid password", 403)
        else:

            new_password = request.form.get("new_password")

            if not new_password:
                return apology("Password can't be empty")
            if new_password != request.form.get("new_password_copy"):
                return apology("passwords do not much")

            db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_password), session["user_id"])

            return redirect("/logout")

            ###############################################################################################


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
