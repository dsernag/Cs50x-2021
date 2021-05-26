import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

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


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///waves_database.db")


@app.route("/")
@login_required
def index():
    """This is the intro to my webpage"""

    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":

        # Check the variables:
        codigo = request.form.get("color")
        cantidad = request.form.get("cantidad")
        talla = request.form.get("talla")

        # Verificar que sí se escogió color, talla y cantidad
        if not codigo:
            return apology("Debes escoger alguna sudadera", 400)
        elif not talla:
            return apology("Debes escoger alguna talla", 400)
        elif cantidad is None:
            return apology("Debes escoger la cantidad", 400)
        # La cantidad debe ser un entero:
        try:
            shares = int(cantidad)

            # Debe ser mayor que 0:
            if shares < 1:
                return apology("Debes seleccionar una cantidad positiva", 400)
        except ValueError:
            return apology("Debes seleccionar una cantidad positiva", 400)

        # Actualizar la cantidad en la base de datos
        db.execute("UPDATE inventario SET cantidad = cantidad + ? WHERE color = ? AND talla = ?", shares, codigo, talla)

        # Crear la transacción!
        db.execute("INSERT INTO transactions (userID, color, cantidad, t_trans, talla) VALUES(?, ?, ?, ?, ?)",
                   session['user_id'], codigo.upper(), cantidad, "compra", talla.upper())
        flash("Compra Exitosa!!!!")
        return redirect("/")
    else:
        colores = db.execute("SELECT DISTINCT(color) FROM inventario")
        tallas = db.execute("SELECT DISTINCT(talla) FROM inventario")
        return render_template("buy.html", colores=colores, tallas=tallas)


@app.route("/history")
@login_required
def history():

    historial = db.execute("SELECT * FROM transactions")
    return render_template("history.html", historial=historial)

@app.route("/inventario")
@login_required
def inventario():

    inventario = db.execute("SELECT * FROM inventario")
    return render_template("inventario.html", inventario=inventario)


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
        codigo = request.form.get("codigo")
        #Get the route to that image
        image_file = url_for('static', filename=codigo)+".jpg"
        return render_template("quoted.html", codigo=codigo, image_file=image_file)

    else:
        quote = db.execute("SELECT DISTINCT(color) FROM inventario")
        return render_template("quote.html", quote=quote)


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

    if request.method == "POST":

        # Check the variables:
        codigo = request.form.get("color")
        cantidad = request.form.get("cantidad")
        talla = request.form.get("talla")

        # Verificar que se escogió sudadera, talla y cantidad
        if not codigo:
            return apology("Debes escoger alguna sudadera", 400)
        elif not talla:
            return apology("Debes escoger alguna talla", 400)
        elif cantidad is None:
            return apology("Debes escoger la cantidad")

        # Debe ser un integer:
        try:
            shares = int(cantidad)

            # Debe ser mayor a 0:

            if shares < 1:
                return apology("Debes seleccionar una cantidad positiva", 400)
        except ValueError:
            return apology("Debes seleccionar una cantidad positiva", 400)

        # Buscar la cantidad de sudadares:
        sudaderas = db.execute("SELECT * FROM inventario WHERE color = ? AND talla = ?", codigo, talla)[0]

        # verificar que la cantidad vendida sí esté en el inventario
        if shares > int(sudaderas['cantidad']):
           return apology("No tienes esa cantidad de sudaderas para vender :(", 400)

        # Actualizar la cantidad en la base de datos
        db.execute("UPDATE inventario SET cantidad = cantidad - ? WHERE color = ? AND talla = ?", shares, codigo, talla)

        # Crear la transacción!
        db.execute("INSERT INTO transactions (userID, color, cantidad, t_trans, talla) VALUES(?, ?, ?, ?, ?)",
                   session['user_id'], codigo.upper(), cantidad, "venta", talla.upper())
        flash("Venta Exitosa!!!!")
        return redirect("/")
    else:
        colores = db.execute("SELECT DISTINCT(color) FROM inventario")
        tallas = db.execute("SELECT DISTINCT(talla) FROM inventario")
        return render_template("sell.html", colores=colores, tallas=tallas)
#
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)