# THE WAVE INVENTORY
#### Video Demo:  [https://youtu.be/oKv7nM4DWUY](https://youtu.be/oKv7nM4DWUY)
#### Description:

Hi everyone! My name is David Serna Gutiérrez, I'm from Medellín Colombia and This is my CS50 final project.

After completing all the labs and problems sets from the course, I've get inspired by the last problem (finance).

Actually I'm selling sport pants. I'd created a python simple program based on a Google Drive Sheet. It's really simple, and don't have any interactive.

Fortunelly the problem set from week 9 allows me to think that is possible to create a interactive web page where keep my purchases and sales, also keeping track the transactions that are made.

Before made anything I should define a database (waves_database). In the database must be 3 tables:

1. **users:** Here stores the registered users

    * *id:* Keep and unique identifier for every user that is registered
    * *username:* Make sure that that has an username (In python code I check that there are unique usernames)
    * *hash:* Stores the passwords through a hash transformation from the werkzeug library

2. **transactions:** Keep the transactions madeG
    * *id:* unique identifier for every transaction
    * *userID:* Register the ID from the user that made the transaction
    * *color:* Store the sport pant color
    * *cantidad:* Store the ammount of sport pant involved in the transaction
    * *transacted:* The precise date and hour the transaction was made
    * *t_trans:* What kind of transaction (buying or selling)
    * *talla:* The size of the sport pant

3. **inventario:** The inventory was previously made on a *.csv* file. Imported via sqlite3 .mode csv. Here is displayed the 5 colors by 4 sizes availabe and what ammount there are.

I made a web application where you must register to get access. Is basically the same system from problem set 9.

Then you can log in with your user and password. Also the same system form problem set 9.

In the webpage there are some options:

* **Productos:** Here you can check the products I sell with an image asociated. It was the most dificult part to allow the user to inspect the list of colors and with that choice display the image. Thansk to the function `url_for` from flask was possible.

* **Comprar:** Here you can buy the sport pants. Must select a color, size and quantity. It checks that you must select a color, also a size, and off course a valid number (positive integer)

* **Vender:** Here you can sell the sport pants. Must be sure to sell an amount that be available in the inventory. Also checks that the user select a valid color and size, and off course a positive integer in quantity

* **Historial** Get an history of the transacctions. It shows the user, size, color, kind of transaction and date. This is really usefull to mantain a track from the transactiones all way long.

* **Inventario:** Show the summary inventory. Combining python and Flask (JINJA2) is possible to insert the rows dynamically.

Also in the index I've install a Javascript script to draw some lines.

Any questions, this is my email: [dsernag@unal.edu.co](dsernag@unal.edu.com)

Thanks to all CS50 team!!!!