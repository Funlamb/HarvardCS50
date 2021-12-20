import os

from cs50 import SQL
from flask import Flask, flash, jsonify, session, request, render_template, redirect

# Configure application
app = Flask(__name__)

# ensure templates are reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

# Configure DB
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

    else:
        # Add Birthday to table
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        return redirect("/")

# Deletes a birthday and reorders the list
@app.route("/delete", methods=["GET", "POST"])
def delete():
    if request.method =="POST":
        # Get id to delete
        id = request.form.get("birthdayID")
        print ("Delete ID: " + id)
        db.execute("DELETE FROM birthdays WHERE id=?", id)

        # Reorder the DB
        db.execute("UPDATE birthdays SET id=id-1 WHERE id>?", id)

        return redirect("/")

# Edit screen a birthday
@app.route("/edit_screen", methods=["GET", "POST"])
def edit_screen():
    if request.method == "POST":
        id = request.form.get("editID")
        # birthday = db.execute("SELECT * FROM birthdays WHERE id=?", id)
        session['my_var'] = id
        return redirect('/edit')

@app.route("/edit", methods=["GET", "POST"])
def edit():
    if request.method == "GET":
        id = session.get('my_var', None)
        birthday = db.execute("SELECT * FROM birthdays WHERE id=?", id)
        for item in birthday:
            print (item)

        return render_template("/edit.html", birthday=birthday)

@app.route("/edit_DB", methods=["GET", "POST"])
def edit_DB():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        edit_id = request.form.get("edit_id")
        print (name + month + day + edit_id)
        db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id=?", name, month, day, edit_id)
        return redirect("/")