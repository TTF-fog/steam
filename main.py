import tkinter

import matplotlib
import tkinter as tk
from waitress import serve
from flask import *
app = Flask(__name__)


@app.route('/')
def hello():
    return 'Hello, World!'
@app.route('/data', methods=['POST'])
def handle_post():
    data = request.get_json()  # get data sent in the POST request
    print(data)  # print the data to console
    return 'Success', 200
app.run(host="0.0.0.0")


matplotlib.use('TkAgg')
# from matplotlib import style
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure

import customtkinter
import gunicorn


def app(environ, start_response):
    data = b"Hello, World!\n"
    start_response("200 OK", [
        ("Content-Type", "text/plain"),
        ("Content-Length", str(len(data)))
    ])
    return iter([data])


class GraphPage(tk.Frame):

    def __init__(self, parent, period):
        tk.Frame.__init__(self, parent)
        self.title_label = tk.Label(self, text=f"Moisture over {period}")
        self.title_label.pack()
        self.pack()

    def add_mpl_figure(self, fig):
        self.mpl_canvas = FigureCanvasTkAgg(fig, self)
        self.mpl_canvas.draw()
        self.mpl_canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        self.toolbar = NavigationToolbar2Tk(self.mpl_canvas, self)
        self.toolbar.update()
        self.mpl_canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)


class MPLGraph(Figure):

    def __init__(self):
        Figure.__init__(self, figsize=(5, 5), dpi=100)
        self.plot = self.add_subplot(111)
        self.plot.plot([1, 2, 3, 4, 5, 6, 7], [4, 3, 5, 0, 2, 0, 6])


class App(tkinter.Tk):
    def __init__(self):
        super().__init__()
        self.geometry("400x150")

        self.button = customtkinter.CTkButton(self, text="Generate Report", command=self.button_callbck)
        self.button.pack(padx=20, pady=20)
        self.period = "1 Week"

        combobox = customtkinter.CTkComboBox(self, values=["1 Day", "1 Week"],
                                             command=self.combobox_callback)
        combobox.set("1 Week")
        combobox.pack(padx=20, pady=25)

    def combobox_callback(self, choice):
        self.period = choice

    def button_callbck(self):
        fig = MPLGraph()

        root = tk.Tk()
        graph_page = GraphPage(root, self.period)
        graph_page.add_mpl_figure(fig)

        root.mainloop()


app = App()
app.mainloop()
