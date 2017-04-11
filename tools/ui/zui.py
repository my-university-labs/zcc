import sys
import time
import threading
from PyQt4 import QtCore, QtGui

class MainWindow(QtGui.QMainWindow):
    """main window"""
    def __init__(self, parent=None):


        # init
        super(MainWindow, self).__init__(parent)
        self.setWindowTitle("中文分词")
        self.resize(800, 500)
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
        # when text changed do action
        self.connect(self.win_widget.text_input, QtCore.SIGNAL('textChanged(QString)'), self.on_changed)
        # check
        self.connect( self.win_widget.checkbox1, QtCore.SIGNAL( 'clicked()' ), self.check_mode1 )
        self.connect( self.win_widget.checkbox2, QtCore.SIGNAL( 'clicked()' ), self.check_mode2 )
        # button
        self.connect(self.win_widget.button, QtCore.SIGNAL( 'clicked()' ), self.clear)
        
        #  self.setWindowIcon(QtGui.QIcon(ICONS))
        self.show()

    def on_open(self):
        file = QtGui.QFileDialog.getOpenFileName(self, 'Open')
        try:
            self.statusBar().showMessage("准备中...")
            # do thread function
            self.bwThread = DealFile(file, 
                self.win_widget.checkbox1.isChecked(), 
                self.win_widget.checkbox2.isChecked())
            self.bwThread.finishSignal.connect(self.action_end)
            self.bwThread.statusSignal.connect(self.show_status)
            self.bwThread.start()
            

        except:
            self.statusBar().showMessage("Error!")

    def action_end(self, ls):
        self.win_widget.text_show.setText(ls)
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
        result = split_sentence(self.win_widget.text_input.toPlainText())
        self.win_widget.text_show.setText(result)
        self.statusBar().showMessage(self.win_widget.text_input.toPlainText())
    def check_mode1(self):
        mode = self.win_widget.checkbox1.isChecked()
        test_mode = self.win_widget.checkbox2.isChecked()
        if self.win_widget.checkbox1.isChecked():
            self.statusBar().showMessage('使用大颗粒度模式')
        else:
            self.statusBar().showMessage('使用小颗粒度模式')
    def check_mode2(self):
        mode = self.win_widget.checkbox1.isChecked()
        test_mode = self.win_widget.checkbox2.isChecked()
        if self.win_widget.checkbox2.isChecked():
            self.statusBar().showMessage('使用检验模式')
        else:
            self.statusBar().showMessage('使用普通模式')

    def clear(self):
        self.win_widget.text_show.setText("")
        self.win_widget.text_input.setText("")
        self.statusBar().showMessage('清除成功')

    def on_changed(self, text):
        if text == "":
            self.win_widget.text_show.setText("")
            self.statusBar().showMessage("就绪")
        else:
            
            self.statusBar().showMessage("正在分词...")
            self.win_widget.text_show.setText(result)
            self.statusBar().showMessage("完成")
           
            
            # # do thread function
            # self.bwThread2 = DealSentence(text, mode, test_mode)
            # self.bwThread2.finishSignal.connect(self.action_end)
            # self.bwThread2.start()
           


class WinWidget (QtGui.QWidget) :
    """text area"""
    def __init__(self, parent):
        super(WinWidget, self).__init__(parent)
        grid_layout = QtGui.QGridLayout()
        grid_layout.setSpacing(10)
        self.text_show = QtGui.QTextEdit()
        self.text_show.setText("")
        grid_layout.addWidget(self.text_show, 0, 0, 1, 3)
          
        self.checkbox1 = QtGui.QCheckBox( "较大颗粒模式" )
        self.checkbox2 = QtGui.QCheckBox( "检验模式" )
        self.button = QtGui.QPushButton( "清空内容")
        
        grid_layout.addWidget(self.checkbox1,1,0)
        grid_layout.addWidget(self.checkbox2,1,1)
        grid_layout.addWidget(self.button, 1,2)
        
        

        self.text_input = QtGui.QLineEdit(self)
        grid_layout.addWidget(self.text_input, 2, 0, 5, 3)

        self.setLayout(grid_layout)


class DealFile(QtCore.QThread):
    """ threading action """
    finishSignal = QtCore.pyqtSignal(str)
    statusSignal = QtCore.pyqtSignal(str)

    def __init__(self ,file , mode, test_mode, parent=None,):
        super(DealFile, self).__init__(parent)
        self.file = file
        self.mode = mode
        self.test_mode = test_mode
    def deal_file(self):
        try:
            split_file(self.file, self.mode, self.test_mode)
            with open(TMP_FILE, "r") as f:
                result = f.readlines()
            self.finishSignal.emit("".join(result))
        except:
            print("Error")

    def deal_status(self):
        last_status = -1
        status = 0
        while last_status != status:
            time.sleep(0.1)
            last_status = status
            status = get_status()
            self.statusSignal.emit("已经处理" + str(status) + "行")
        print("finish")

    def run(self):
        t1 = threading.Thread(target=self.deal_file, args=())
        t2 = threading.Thread(target=self.deal_status, args=())
        t1.start()
        t2.start()

class DealSentence(QtCore.QThread):
    """ threading action """
    finishSignal = QtCore.pyqtSignal(str)
   
    def __init__(self ,sentence , mode, test_mode, parent=None,):
        super(DealSentence, self).__init__(parent)
        
        self.sentence = sentence
        self.mode = mode
        self.test_mode = test_mode
    def deal_sentence(self):
        try:
            self.finishSignal.emit(split_sentence(self.sentence, self.mode, self.test_mode))
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
