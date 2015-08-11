import sqlite3
db = sqlite3.connect("yada.sqlite")
iterator = db.cursor()
iterator.execute("create table donuts (customer, glazed, cake, due)")
iterator.execute("insert into donuts values ('jeff', 10, 10, 30)")
iterator.execute("select * from donuts")
for customer in iterator.fetchall():
	print(customer)
iterator.execute("insert into donuts values ('kevin', 13, 13, 60)")
iterator.execute("select * from donuts")
for customer in iterator.fetchall():
	print(customer)
