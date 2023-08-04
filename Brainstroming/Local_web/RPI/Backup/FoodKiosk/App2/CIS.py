import tkinter as tk
from tkinter import ttk
# from tkinter import *
from tkinter.ttk import *


import MySQLdb

mysqlusername = "Vendigo_S1"
mysqlpassword = "vs12345"
mysqlDB = "Vendigo_S1"

def submitact():

    user = Username.get()
    passw = password.get()
    print(f"credentials entered: {user} {passw}")

    logintodb(user, passw)


def logintodb(user, passw):

    # If password is enetered by the
    # user
    if passw:
        db = MySQLdb.connect("localhost","admin","vs12345","Vendigo_S1" )
        cursor = db.cursor()

    # A Table in the database
    savequery = "SELECT * FROM orders"

    try:
        cursor.execute(savequery)
        myresult = cursor.fetchall()
        db.close()
        # Printing the result of the
        # query
        row=[]
        for x in myresult:
            row.append(x)
        if (int(user)>0) and (int(user)<11):
            if(row[int(user)-1][3]) ==(int(passw)):
                print("Access Granted")
                status='1'
                db = MySQLdb.connect("localhost","admin","vs12345","Vendigo_S1" )
                cursor1 = db.cursor()
                cursor1.execute ("""
                UPDATE BoxStatus  
                SET BoxStatus=%s
                WHERE BoxNumber=%s
                """, (status, user))
                #DB_Update = "UPDATE BoxStatus SET BoxStatus = '1' WHERE BoxNumber = 'box_number'"
                db.commit()
                db.close()
         
    except:
        db.rollback()
        print("Connection Error!!!!!!!!!!!!")
  
 
root = tk.Tk()
root.geometry("480x800")
root.resizable(False, False)
root.title("~~~~~~~~~~~~~Vendigo Locker Console~~~~~~~~~~~~~")
  

style = ttk.Style()
style.configure("TFrame", foreground="black", background="purple", font =('Helvetica', 18, 'bold'))


main_frame = ttk.Frame(root, 
    style='main_frame.TFrame', 
    height=800, 
    width=480, 
    cursor='question_arrow', 
    relief='sunken') 
main_frame.pack(fill='x') 

# main_frame.place(anchor='center', relx=0.5, rely=0.5)

# l1 = ttk.Label(text="Test", style="BW.TLabel")
# l2 = ttk.Label(text="Test", style="BW.TLabel")
# style.configure("label.style", foreground="white",font =('Helvetica', 18, 'bold')) 
# Defining the first row

# photo = tk.PhotoImage("main_frame",file='./image/logo.png')
# image_label = ttk.Label(
#     root,
#     image=photo,
#     text='vendigo',
#     compound='image'
# )

# image_label.image = photo # keep a reference!
# image_label.pack()

lblfrstrow = ttk.Label(root, text ="Box")
lblfrstrow.place(x = 180, y = 120)
 
Username = ttk.Entry(root, width = 35)
Username.place(x = 220, y = 120, width = 100)

lblsecrow = ttk.Label(root, text ="OTP")
lblsecrow.place(x = 180, y = 150)
 
password = ttk.Entry(root, width = 35)
password.place(x = 220, y = 150, width = 100)

submitbtn = ttk.Button(root, text ="Open", command = submitact)
submitbtn.place(x = 240, y = 185, width = 55)

root.mainloop()
