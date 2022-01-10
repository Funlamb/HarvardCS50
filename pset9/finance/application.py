import os

from datetime import datetime
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
    # get user's stock
<<<<<<< HEAD
    stocks = get_users_stocks()
=======
    stocks = db.execute("SELECT stocks.symbol, SUM(transactions.quantity) FROM users JOIN transactions ON transactions.userID=users.id JOIN stocks ON transactions.stockID=stocks.id WHERE users.id=? GROUP BY stocks.symbol HAVING SUM(transactions.quantity) > 0", session['user_id'])
>>>>>>> f61beb76c83bb0bb3e81c044d9e80c98a7413797

    # the current price of each stock,
    value_of_users_stocks = 0
    for s in stocks:
        # find the stock price and name
        stock = lookup(s['symbol'])
        # add it to current dict
        s['stock_name'] = stock['name']
        s['stock_price'] = stock['price']
        s['stocks_value'] = stock['price'] * s['SUM(transactions.quantity)']
        value_of_users_stocks = value_of_users_stocks + s['stocks_value']

    # get users cash on hand
    cash = get_users_cash()

    # users total assets
    value_of_users_stocks = value_of_users_stocks + cash
    return render_template("index.html", stocks=stocks, cash=cash, value_of_users_stocks=value_of_users_stocks)


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
        number_of_shares = request.form.get('shares')
        if not number_of_shares.isdigit():
            return apology("Please enter a positive whole number")
        number_of_shares = int(number_of_shares)
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
        userID = session['user_id']  # session['user_id'] returns {'id':1}
        stockID = db.execute("SELECT id FROM stocks WHERE symbol = ?", stock_symbol)
        date_time_of_trade = get_date_and_time()
        db.execute("INSERT INTO transactions (userID, stockID, quantity, price, time) VALUES (?, ?, ?, ?, ?)",
                   userID, stockID[0]['id'], number_of_shares, stock_price, date_time_of_trade)

        # remove money for users account
        remaining_cash = cash_on_hand - cost_total_of_wanted_shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_cash, stockID[0]['id'])
<<<<<<< HEAD

        # return render_template("bought.html", shares=number_of_shares, stock=stock_name, cost_of_stock=stock_price, cash=cost_total_of_wanted_shares, time=date_time_of_trade)
        return redirect("/")

=======
        print(cost_total_of_wanted_shares)
        return render_template("bought.html", shares=number_of_shares, stock=stock_name, cost_of_stock=stock_price, cash=cost_total_of_wanted_shares, time=date_time_of_trade)
>>>>>>> f61beb76c83bb0bb3e81c044d9e80c98a7413797

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # get user's transactons history
    # Symbol 	Shares 	Price 	Transacted
    transactions = db.execute(
        "SELECT stocks.symbol, transactions.quantity, transactions.price, transactions.time FROM stocks JOIN transactions ON transactions.stockID=stocks.id WHERE transactions.userID=?", session['user_id'])
    print(transactions)
    return render_template("history.html", transactions=transactions)


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
        """register user"""
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
    if request.method == "POST":
        """Sell shares of stock"""
        stock_to_sell = request.form.get("symbol")
        quantity_to_sell = int(request.form.get("shares"))

        # check if a valid stock symbol has been entered
        stock_data = lookup(stock_to_sell)
        if stock_data == None:
            return apology("Need a valid stock symbol")

        stock_price = stock_data['price']

        # find out how many shares of that stock the user has
        user_quantity_of_stock = db.execute("SELECT stocks.symbol, SUM(transactions.quantity) FROM users JOIN transactions ON transactions.userID=users.id JOIN stocks ON transactions.stockID=stocks.id WHERE users.id=? AND stocks.symbol=?",
                                            session['user_id'], stock_to_sell)[0]['SUM(transactions.quantity)']

        # test if user has sufficiant stocks to sell
        if user_quantity_of_stock < quantity_to_sell:
            return apology('You do not have enough shares to sell')

        # get stockID
        stockID = db.execute("SELECT id FROM stocks WHERE symbol=?", stock_to_sell)[0]['id']

        # enter in the transaction
        # invert quantity to sell to create correct transaction
        quantity_to_sell = quantity_to_sell * -1
        date_time_of_trade = get_date_and_time()
        db.execute("INSERT INTO transactions (userID, stockID, quantity, price, time) VALUES (?, ?, ?, ?, ?)",
                   session['user_id'], stockID, quantity_to_sell, stock_price, date_time_of_trade)

        # add money to users account
<<<<<<< HEAD
        users_current_cash = get_users_cash()
        value_of_shares_sold = stock_price * quantity_to_sell * -1
        user_new_cash_balance = users_current_cash + value_of_shares_sold
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_new_cash_balance, session['user_id'])

        return redirect("/")
        # return render_template("sold.html", shares=quantity_to_sell, stock=stock_data['symbol'], cost_of_stock=stock_price, transaction_value=value_of_shares_sold, time=date_time_of_trade)
    # get list of users stocks
    else:
        stocks = get_users_stocks()
=======
        cash_on_hand = db.execute("SELECT cash FROM users WHERE id=?", session['user_id'])
        cash_on_hand = cash_on_hand[0]['cash']
        cost_total_of_sold_shares = stock_price * quantity_to_sell * -1
        remaining_cash = cash_on_hand + cost_total_of_sold_shares
        # print("Here ") # + cost_total_of_sold_shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_cash, session['user_id'])
        cost_of_shares = cost_total_of_sold_shares
        return render_template("sold.html", shares=quantity_to_sell, stock=stock_data['symbol'], cost_of_stock=stock_price, cash=cost_of_shares, time=date_time_of_trade)
    # get list of users stocks
    else:
        stocks = db.execute("SELECT stocks.symbol FROM stocks JOIN transactions ON transactions.stockID=stocks.id WHERE transactions.userID=? GROUP BY stocks.symbol HAVING SUM(transactions.quantity) > 0", session['user_id'])
>>>>>>> f61beb76c83bb0bb3e81c044d9e80c98a7413797
        return render_template("sell.html", stocks=stocks)


def get_users_stocks():
    stocks = db.execute("SELECT stocks.symbol, SUM(transactions.quantity) FROM stocks JOIN transactions ON transactions.stockID=stocks.id WHERE transactions.userID=? GROUP BY stocks.symbol HAVING SUM(transactions.quantity) > 0",
                        session['user_id'])
    return stocks


def get_users_cash():
    cash = db.execute('SELECT * FROM users WHERE id=?', session['user_id'])[0]['cash']
    return cash


def get_date_and_time():
    # current date and time
    now = datetime.now()
    # date and time format: dd/mm/YYYY H:M:S
    format = "%Y/%m/%d %H:%M:%S"
    # format datetime using strftime()
    time1 = now.strftime(format)
    return time1


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
