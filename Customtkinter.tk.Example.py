#python.exe pip -m install customtkinter

import customtkinter as tk

class App(tk.CTk):
	'''Main Application'''
	def __init__(self):
		super().__init__()
		self.title("Custom Tkinter")
		self.geometry("800x400")
		self.resizable(True, True)
		self.config(bg="white")

		self.label = tk.CTkLabel(self, text="Hello World", bg_color="white", fg_color="white", text_color="black")
		self.label.pack(pady=10)

		self.button = tk.CTkButton(self, text="Click Me", bg_color="white", fg_color="blue", text_color="white", command=self.change_text)
		self.button.pack(pady=10)

		self.frame = tk.CTkFrame(self, bg_color="blue", fg_color="grey")
		self.frame.pack(pady=10, fill="both", expand=True)

		self.un = tk.CTkEntry(self.frame, bg_color="white", fg_color="grey", placeholder_text_color="white", placeholder_text="Username")
		self.un.pack(pady=10)

		self.pw = tk.CTkEntry(self.frame, bg_color="white", fg_color="grey", placeholder_text_color="white", placeholder_text="Password", show="*")
		self.pw.pack(pady=10)

		self.cb = tk.CTkCheckBox(self.frame, text="Remember username")
		self.cb.pack(pady=10)d

	def change_text(self):
		'''Change the text of the label'''
		self.label.config(text="Button Clicked")
	

if __name__ == "__main__":
	app = App()
	app.mainloop()
