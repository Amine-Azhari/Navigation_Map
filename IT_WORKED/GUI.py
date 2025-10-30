from tkinter import *
from PIL import Image, ImageTk
import math
from ctypes import WinDLL, c_char_p

lib = WinDLL(r"C:\Users\w\OneDrive\Bureau\1A IR\Github\Processin\Map ways\V2_manual\dijkstra.dll")
lib.dijkstra_python.argtypes = [c_char_p, c_char_p]
lib.dijkstra_python.restype = c_char_p 


adjacency = {
    "K": ["X2"],
    "L": ["X3"],
    "I": ["X4", "X6"],
    "J": ["X5"],
    "M": ["X8"],
    "H": ["X7", "X8"],
    "N": ["X10"],
    "O": ["X10"],
    "P": ["X12"],
    "C": ["X11", "X16"],
    "Q": ["X13"],
    "B": ["X13"],
    "A": ["X14"],
    "SI": ["X10"],
    "SU": ["X15"],
    "X1": ["X2", "X5"],
    "X2": ["K", "X1", "X3"],
    "X3": ["L", "X2", "X4"],
    "X4": ["I", "X3", "X8"],
    "X5": ["J", "X6", "X1"],
    "X6": ["I", "X5", "X7"],
    "X7": ["X6", "H", "X16"],
    "X8": ["M", "H", "X9", "X4"],
    "X9": ["X8", "X12", "X10"],
    "X10": ["X9", "N", "O", "SI"],
    "X11": ["X12", "C", "X13"],
    "X12": ["P", "X11", "X9"],
    "X13": ["Q", "B", "X11", "X17"],
    "X14": ["X18", "A"],
    "X15": ["X17", "SU"],
    "X16": ["C", "X18", "X7"],
    "X17": ["X13", "X18", "X15"],
    "X18": ["X14", "X16", "X17"]
}


coords = {
    "K": (182, 351), "L": (338, 299), "I": (310, 375), "J": (270, 483), "M": (446, 271),
    "H": (452, 355), "N": (495, 188), "O": (538, 206), "P": (662, 287), "C": (682, 393),
    "Q": (739, 278), "B": (745, 402), "A": (861, 438), "SI": (549, 142), "SU": (862, 174),
}


nodes =  {
    "K": (182, 351), "L": (338, 299), "I": (310, 375), "J": (270, 483), "M": (446, 271),
    "H": (452, 355), "N": (495, 188), "O": (538, 206), "P": (662, 287), "C": (682, 393),
    "Q": (739, 278), "B": (745, 402), "A": (861, 438), "SI": (549, 142), "SU": (862, 174),
    "X1": (205, 399), "X2": (232, 338), "X3": (345, 336), "X4": (367, 336), "X5": (304, 429),
    "X6": (348, 437), "X7": (454, 450), "X8": (455, 333), "X9": (514, 342), "X10": (515, 180),
    "X11": (680, 345), "X12": (645, 340), "X13": (746, 330), "X14": (834, 403), "X15": (830, 269),
    "X16": (688, 450), "X17": (802, 331), "X18":(806, 419)
}

def distance(a, b):
    x1, y1 = nodes[a]
    x2, y2 = nodes[b]
    return round(math.hypot(x2 - x1, y2 - y1))

"""
print("Edge adjacency_list[][10] = {")  # taille max par ligne 10, exemple
for node, neighbors in adjacency.items():
    edges = []
    for n in neighbors:
        d = distance(node, n)
        edges.append(f"{{'{n}', {d}}}")
    edges_str = ", ".join(edges)
    print(f"    // {node}")
    print(f"    {{ {edges_str} }},")
print("};")
"""

class GUI():
    def __init__(self):
        self.window = Tk()
        self.create_canvas()
        self.window.bind('<Escape>', lambda event: self.window.destroy())
        self.quit = Button(self.window, text ='quit' ,command = lambda: self.window.destroy())
        self.quit.pack()
        self.window.mainloop()

    def create_canvas(self):
        self.h = 600
        self.w = 1100
        self.canvas = Canvas(self.window, width=self.w, height=self.h)
        self.canvas.pack()

        self.bg_image = Image.open("campus illberg.png") 
        self.bg_image = self.bg_image.resize((self.w, self.h))
        self.bg_photo = ImageTk.PhotoImage(self.bg_image)
        self.canvas.create_image(0, 0, anchor=NW, image=self.bg_photo)

        r = 15
        for i, (label, (x, y)) in enumerate(coords.items()):
            if i >= 15:
                break
            self.oval(x, y, r, label)

        self.window.bind('<Button-1>', self.on_click)

    def coordinates(self, event):
        print(event.x, event.y)

    def oval(self,x,y,r,label):
        self.canvas.create_oval(x-r, y-r, x+r, y+r, fill="#FFFFFF", outline="#4757EC", width=3)
        self.canvas.create_text(x, y, text=label, fill="#4757EC", font=("Helvetica", 12, "bold"))
    
    def clickedNode(self, event):
        x = event.x
        y = event.y
        margin = 15
        for key, coord in nodes.items():
            if (x - margin <= coord[0] <= x + margin) and (y - margin <= coord[1] <= y + margin):
                print(key)
                return key
                break
        return None
    
    def on_click(self, event):
        node = self.clickedNode(event)
        if node is None:
            return
        if not hasattr(self, 'start'):
            self.start = node
            print("Start:", node)
        else:
            end = node
            print("End:", node)

            path_bytes = lib.dijkstra_python(self.start.encode('utf-8'), end.encode('utf-8'))
            path = path_bytes.decode('utf-8')
            print("Chemin reçu depuis C :", path)

            path_list = path.split(',')
            print("Liste des nœuds :", path_list)
            self.way(path_list)


    def way(self, path):
        for i in range(len(path) - 1):
            xi, yi = nodes.get(path[i])
            xj, yj = nodes.get(path[i + 1])
            self.canvas.create_line(xi, yi, xj, yj, fill="blue", width=6)


    



if __name__ == "__main__":
    interface = GUI()
