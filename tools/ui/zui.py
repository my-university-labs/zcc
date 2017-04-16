import sys
import time
import threading
from PyQt4 import QtCore, QtGui

from zui_config import *


class MainWindow(QtGui.QMainWindow):
    """main window"""

    def __init__(self, parent=None):
        # init
        super(MainWindow, self).__init__(parent)
        self.setWindowTitle(WINDOWS_TITLE)
        self.resize(1200, 800)
        # widget input...
        self.win_widget = WinWidget(self)
        widget = QtGui.QWidget()
        layout = QtGui.QVBoxLayout(widget)
        layout.addWidget(self.win_widget)
        self.setCentralWidget(widget)
        # status bar
        self.statusBar().showMessage("就绪")
        # menu bar
        menu_bar = self.menuBar()
        self.file = menu_bar.addMenu('&File')
        open = self.file.addAction('Open')
        self.connect(open, QtCore.SIGNAL('triggered()'), self.on_open)
        save = self.file.addAction('Save')
        self.connect(save, QtCore.SIGNAL('triggered()'), self.on_save)
        self.file.addSeparator()
        close = self.file.addAction("Close")
        self.connect(close, QtCore.SIGNAL('triggered()'), self.on_close)

        # button 词法
        self.connect(self.win_widget.button,
                     QtCore.SIGNAL('clicked()'), self.clear)
        # button1 语法
        self.connect(self.win_widget.button1,
                     QtCore.SIGNAL('clicked()'), self.do_parser)
        # button2 语义
        self.connect(self.win_widget.button2,
                     QtCore.SIGNAL('clicked()'), self.clear)
        # button3 ASM
        self.connect(self.win_widget.button2,
                     QtCore.SIGNAL('clicked()'), self.clear)

        #  self.setWindowIcon(QtGui.QIcon(ICONS))
        self.show()

    def do_parser(self):
        result = self.win_widget.text_input.toPlainText()
        print(result)

    def on_open(self):
        file = QtGui.QFileDialog.getOpenFileName(self, 'Open')
        print(file)
        # try:
        self.statusBar().showMessage("准备中...")
        # do thread function
        self.bwThread = DealFile(file)
        self.bwThread.finishSignal.connect(self.action_end)
        self.bwThread.statusSignal.connect(self.show_status)
        self.bwThread.start()

        # except:
        #     self.statusBar().showMessage("Error!")

    def action_end(self, ls):
        self.win_widget.text_input.setText(ls)
        self.statusBar().showMessage("就绪")

    def show_status(self, s):
        self.statusBar().showMessage(s)

    def on_save(self):
        self.show_result()
        # self.label.setText("save")

    def on_close(self):
        self.close()

    def contextMenuEvent(self, event):
        self.file.exec_(event.globalPos())

    def show_result(self):
        # result = split_sentence(self.win_widget.text_input.toPlainText())
        self.win_widget.text_show.setText(result)
        # self.statusBar().showMessage(self.win_widget.text_input.toPlainText())

    def clear(self):
        self.win_widget.text_show.setText("")
        self.statusBar().showMessage('清除成功')


class WinWidget (QtGui.QWidget):
    """text area"""

    def __init__(self, parent):
        super(WinWidget, self).__init__(parent)
        grid_layout = QtGui.QGridLayout()
        grid_layout.setSpacing(10)
        self.text_input = QtGui.QTextEdit()
        self.text_show = QtGui.QTextEdit()
        self.text_show.setText("show")
        self.text_input.setText("input")
        grid_layout.addWidget(self.text_input, 0, 0, 1, 2)
        grid_layout.addWidget(self.text_show, 0, 2, 1, 2)

        self.button = QtGui.QPushButton("词法分析")
        self.button1 = QtGui.QPushButton("语法分析")
        self.button2 = QtGui.QPushButton("语义分析")
        self.button3 = QtGui.QPushButton("ASM")
        grid_layout.addWidget(self.button, 1, 0)
        grid_layout.addWidget(self.button1, 1, 1)
        grid_layout.addWidget(self.button2, 1, 2)
        grid_layout.addWidget(self.button3, 1, 3)

        self.setLayout(grid_layout)


class DealFile(QtCore.QThread):
    """ threading action """
    finishSignal = QtCore.pyqtSignal(str)
    statusSignal = QtCore.pyqtSignal(str)

    def __init__(self, file):
        super(DealFile, self).__init__()
        self.file = file

    def deal_file(self):
        try:
            with open(self.file, "r") as f:
                result = f.readlines()
            print(result)
            self.finishSignal.emit("".join(result))
        except:
            print("Error")

    def run(self):
        print("deal", self.file)
        t1 = threading.Thread(target=self.deal_file, args=())
        t1.start()


class DealSentence(QtCore.QThread):
    """ threading action """
    finishSignal = QtCore.pyqtSignal(str)

    def __init__(self, sentence, mode, test_mode, parent=None,):
        super(DealSentence, self).__init__(parent)

        self.sentence = sentence
        self.mode = mode
        self.test_mode = test_mode

    def deal_sentence(self):
        try:
            self.finishSignal.emit(split_sentence(
                self.sentence, self.mode, self.test_mode))
        except:
            print("Error")

    def run(self):
        t1 = threading.Thread(target=self.deal_sentence, args=())
        t1.start()


def main():

    app = QtGui.QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
