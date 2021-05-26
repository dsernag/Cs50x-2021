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
    # Get user current cash
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session['user_id'])

    # Get user current stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE userID = ? GROUP BY symbol HAVING total_shares > 0;", session['user_id'])

    # calculate the total cash left:
    total_cash_stocks = 0

    for stock in stocks:
        quote = lookup(stock['symbol'])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["total"] = stock["price"] * stock["total_shares"]
        total_cash_stocks = total_cash_stocks + stock["total"]

    total_cash = total_cash_stocks + user_cash[0]['cash']

    return render_template("index.html", stocks=stocks, user_cash=user_cash[0], total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":

        # Check the variables:
        symbol = request.form.get("symbol")
        price = lookup(symbol)
        shares = request.form.get("shares")

        # Get the money from the user:
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Check there is a symbol a price and shares:
        if not symbol:
            return apology("You must provide a valid symbol", 400)
        elif price is None:
            return apology("You must provide a valid symbol")

        # Shares must be an integer:
        try:
            shares = int(shares)

            # Shares must be upper than 1:

            if shares < 1:
                return apology("Shares must be a positive integer", 400)
        except ValueError:
            return apology("Shares must be a positive integer", 400)

        # After checking errors we must continue
        # Multiply price*shares:
        shares_price = shares * price['price']

        # Check the user have enough money:
        if user_cash < shares_price:
            return apology("You don't have enough money :(", 400)

        # Now make the buy, updating the cash:
        else:
            # Update the money from the account
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", shares_price, session['user_id'])

            # After creating a new table #DATE is from default
            db.execute("INSERT INTO transactions (userID, symbol, shares, price) VALUES(?, ?, ?, ?)",
                       session['user_id'], symbol.upper(), shares, price['price'])

            flash("Successful Transaction!")
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM transactions WHERE userID = ?", session["user_id"])
    return render_template("history.html", stocks=stocks)


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

    if request.method == "POST":

        # Get the quote note
        quote = lookup(request.form.get("symbol"))

        # Check there is a quote
        if quote is None:
            return apology("Please provide a valid symbol", 400)

        else:
            return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=quote["price"])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forguet any User id:
    session.clear()

    # If use POST to create an account:

    if request.method == "POST":

        # Define the variables:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Check username exist
        if not username:
            return apology("You must provide a username", 400)

        # Check the username is not duplicate:
        elif len(rows) != 0:
            return apology("The username already exists", 400)

        # Check there is a password
        elif not password:
            return apology("You must provide a password", 400)

        # Check confirmation exist:
        elif not confirmation:
            return apology("You must provide a confirmation password", 400)

        # Check password==confirmation:
        elif not password == confirmation:
            return apology("The passwords doesn't match", 400)

        # If everything is ok:
        else:

            # Create the hash_password:
            hash_pw = generate_password_hash(password)

            # Insert the user:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash_pw)

            # Redirect to homepage
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        # Get the variables:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        try:
            # Shares must be an integer greater than 1
            shares = int(shares)

            if shares < 1:
                return apology("Shares must be an integer", 400)

        except ValueError:
            return apology("Shares must be an integer", 400)

        # Check symbol exist:
        if not symbol:
            return apology("Please submit a real symbol")

        # Everything checked:
        stocks = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE userID = ? AND SYMBOL = ?",
                            session['user_id'], symbol)[0]

        # Check the number of shares = shares from the user
        if shares > stocks['total_shares']:
            return apology("You don't have that ammount of shares", 400)

        price = lookup(symbol)["price"]
        shares_value = price * shares

        # Now made the sell:
        # In the stocks TABLE:
        db.execute("INSERT INTO transactions (userID, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol.upper(), -shares, price)

        # Cash in the users table:
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares_value, session["user_id"])

        # Made IT!!!
        flash("Sold!")
        return redirect("/")
    else:
        stocks = db.execute("SELECT symbol FROM transactions WHERE userID = ? GROUP BY symbol;", session['user_id'])
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)