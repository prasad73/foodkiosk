from tkinter import ttk 
import tkinter as app 
 
app_main_window = app.Tk() 
 
 
def greet(): 
	print(f"Hello {submit_label_Entry_text.get()}!!") 
 
 
submit_button_text = app.StringVar() 
submit_label_Entry_text = app.StringVar() 
submit_button_text.set("Submit") 
s = ttk.Style() 
s.configure('.', background='gray') 
main_frame = ttk.Frame(app_main_window, 
	style='main_frame.TFrame', 
	height=100, 
	width=50, 
	cursor='question_arrow', 
	relief='sunken') 
main_frame.pack(fill='x') 

hi_label = ttk.Label(main_frame, text='Enter Your Name: ' ) 

submit_button = ttk.Button( main_frame, 
	text='Submit Button', 
	style='submit_button.TButton', 
	textvariable=submit_button_text, 
	width=25, 
	command=greet ) 
 
user_entry = ttk.Entry(main_frame, textvariable=submit_label_Entry_text) 
 
hi_label.grid(row=0, column=0) 
user_entry.grid(row=0, column=1) 
submit_button.grid(row=2, columnspan=3, pady=5) 
 
app_main_window.mainloop()