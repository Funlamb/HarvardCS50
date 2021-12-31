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
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # get users cash on hand
    user = db.execute("Select cash From users where id=?", session['user_id'])
    cash_on_hand = user[0]['cash']
    # get price of the stock
    if request.method == "GET":
        # display with users cash on hand
        return render_template("buy.html", cash=cash_on_hand)
    else:
        """Buy shares of stock"""
        
        # make sure user is buying positive shares
        number_of_shares = int (request.form.get('shares'))
        if number_of_shares < 0:
            return apology("Please choose a positive number of shares")
        
        # make sure the number is a whole number
        if not isinstance(number_of_shares, int):
            return apology("Please enter a whole number")
        
        # make sure it is a valid stock
        stock_data = lookup(request.form.get('symbol'))
        if stock_data == None:
            return apology("Invalid Stock Symbol")
            
        stock_symbol = stock_data['symbol']
        stock_name = stock_data['name']
        stock_price = stock_data['price']
        
        # make sure user can purchase that many stocks
        cost_total_of_wanted_shares = number_of_shares * stock_price
        if cash_on_hand < cost_total_of_wanted_shares:
            return apology("You do not have enough capital to purchase these shares")
        
        # create the stock if it doesn't alread exist
        check_for_stock = db.execute("SELECT COUNT(*) AS count FROM stocks WHERE symbol=? LIMIT 1", stock_symbol)
        if check_for_stock[0]["count"] != 1:
            db.execute("INSERT INTO stocks (symbol) VALUES (?)", stock_symbol)
        
        # create the transaction
        
        # remove money for users account
        # put the stocks into the user's account
        return apology("Work on buying stock")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
    if request.method == "POST":
        stock_data = lookup(request.form.get("symbol"))
        if stock_data == None:
            return apology("Need a valid stock symbol")
        stock_symbol = stock_data['symbol']
        stock_name = stock_data['name']
        stock_price = stock_data['price']
        return render_template("quoted.html", stock_name=stock_name, stock_symbol=stock_symbol, stock_price=stock_price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # register user
        # check if name is entered
        username = request.form.get("username")
        if not username:
            return apology("Must enter a username", 400)

        # if username already exists have them put in a new name
        check_for_user = db.execute("SELECT COUNT(*) AS count FROM users WHERE username=? LIMIT 1", username)
        number_of_users_with_that_name = (check_for_user[0].get("count"))
        if number_of_users_with_that_name == 1:
            return apology("That name is already in use")

        # check if user entered a passwords and they match
        password = request.form.get("password")
        check_password = request.form.get("confirmation")
        if not password:
            return apology("Must enter a password")
        if not check_password:
            return apology("Must repeat your password")
        if password != check_password:
            return apology("Passwords must match")
        # add user to database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
        # rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        # session["user_id"] = rows[0]['id']
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
