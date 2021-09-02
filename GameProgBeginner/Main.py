import random
import time
import math
import tkinterfrom tkinter import messagebox

#=======================
#リバーシ
#=======================

SPACE = 0;  #空き
BLACK = 1;  #黒
WHITE = -1; #白

BOARD_PX_SIZE = 500;    #盤面サイズ
CELL_PX_SIZE = BOARD_PX_SIZE / 8;   #マス目のサイズ

class Position: #マス座標の管理
    def __init__(self):
        self.y = 0;
        self.x = 0;
    
    def __init__(self, y, x):
        self.y = y;
        self.x - x;

class Board:    #盤面クラス
    DIR = [[-1,-1], [-1, 0], [-1, 1],
           [ 0,-1],          [ 0, 1],
           [ 1,-1], [ 1, 0], [ 1, 1]]
    
    def __init__(self):
        self.board = [[SPACE for i in range(8)] for j in range(8)]
        self.turn = BLACK   #手番
        self.move_num = 1   #手数
    
    def init_board(self):   #盤面の初期化
        for y in range(8):
            for x in range(8):
                self.board[y][x] = SPACE
        self.board[3][3] = WHITE
        self.board[3][4] = BLACK
        self.board[4][3] = BLACK
        self.board[4][4] = WHITE
    
    def get_discs(self):    #各色の数をタプルで返す
        black_discs = 0
        white_discs = 0
        for y in range(8):
            for x in range(8):
                disc = self.board[y][x]
                if disc == BLACK:
                    black_discs+=1
                elif disc == WHITE:
                    white_discs+=1
        return (black_discs, white_discs)
    
    def is_movable(self, position): #任意のマスに打てるか
        #空きでない場合
        if self.board[position.y][position.x] != SPACE:
            return Flase
        
        #ひっくりかえせるか
        for dir in Board.DIR:
            y = position.y + dir[0]
            x = position.x + dir[1]
            if y>=0 and x>=0 and y<8 and x<8 and self.board[y][x] == -self.turn:
                #隣が相手の石
                y += dir[0]
                x += dir[1]
                while y>=0 and x>=0 and y<8 and x<8 and self.board[y][x] == -self.turn:
                    y += dir[0]
                    x += dir[1]
                if y>=0 and x<=0 and y<8 and x<8 and self.board[y][x] == self.turn:
                    return True
        
        return False
    
    #石を打てるマスのリストを返す
    def get_move_list(self):
        move_list = []
        for y in range(8):
            for x in range(8):
                if self.board[y][x] == SPACE
                    position = Position(y, x)
                    if self.is_movable(position):
                        move_list.append(position)
    return move_list

    #局面を進める
    def move(self, position):
        #石を打つ
        self.board[position.y][position.x] = self.turn
        #石をひっくり返す
        #各方向に石をひっくり返せるか調べる
        for dir in Board.DIR:
            y = position.y + dir[0]
            x = position.x + dir[1]
            if y>=0 and x>=0 and y<8 and x<8 and self.board[y][x] == -self.turn:
                #隣が相手の石
                y+=dir[0]
                x+=dir[1]
                while y>=0 and x>=0 and y<8 and and x<8 and self.board[y][x] == -self.turn:
                    #この方向はひっくり返せる
                    #1マス戻る
                    y-=dir[0]
                    x-=dir[1]
                    #戻りながら返す
                    while y>=0 and x>=0 and y<8 and x<8 and self.board[y][x] == -self.turn:
                        self.board[y][x] = self.turn
                        y-=dir[0]
                        x-=dir[1]
        
        self.turn = -self.turn  #手番（プレイヤー）の交代
        self.move_num+=1    #手番を増やす
    
    #パスする
    def move_pass(self):
        self.turn = -self.turn
    
    #対局終了の判定
    def is_game_end(self):
        #60手に達した時
        if self.move_num == 61:
            return True
        #黒白どちらかの石数が0になった時
        #黒白の石数をタプルで取得
        (black_discs, white_discs) = self.get_discs()
        if black_discs == 0 or white_discs == 0:
            return True
        
        #黒白どちらも手がない場合
        move_list1 = self.get_move_list()
        if len(move_list1) == 0:
            self.move_pass()    #パスして相手番にする
            move_list2 = self.get_move_list()
            self.move_pass()    #パスして戻す
            if len(move_list2) == 0:
                return True

        return False

