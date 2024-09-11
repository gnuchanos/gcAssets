from raylibpy import *

class Colors:
    def __init__(self) -> None:
        self.GPurple0 = Color(  16,  1,   36, 255 )
        self.GPurple1 = Color(  34,  2,   77, 255 )
        self.GPurple2 = Color(  49,  3,  110, 255 )
        self.GPurple3 = Color(  67,  5,  150, 255 )
        self.GPurple4 = Color(  86,  6,  194, 255 )
        self.GPurple5 = Color( 110, 10,  245, 255 )

class SimpleGame:
    def __init__(self) -> None:
        self.ScreenWidth = 1000
        self.ScreenHeight =  600
        self.GameTitle = "Game Title"
        self.Color = Colors()

        self.LeftPad   = Rectangle(10,  self.ScreenHeight/2-75, 10, 150)
        self.RightPad  = Rectangle(980, self.ScreenHeight/2-75, 10, 150)
        self.TopBAR    = Rectangle(0, 0, self.ScreenWidth, 5)
        self.BottomBAR = Rectangle(0, self.ScreenHeight-5, self.ScreenWidth, 5)

        self.BALL      = Rectangle(self.ScreenWidth/2-15, self.ScreenHeight/2-15, 30, 30)
        self.BALLSpeed = 200

        self.LeftEndArea  = Rectangle(-20, 0, 1, self.ScreenHeight)
        self.RightEndArea = Rectangle(self.ScreenWidth+20, 0, 1, self.ScreenHeight)

        self.LeftEndAreaHit  = False
        self.RightEndAreaHit = False

        self.TopBAR_Hit = False
        self.BottomBAR_Hit = False
        self.LeftPad_Hit = False
        self.RightPad_Hit = False

        self.LeftHit = False
        self.UpHit   = False
        self.DownHit = False
        
        self.keyW    = False
        self.keyS    = False

        self.LeftPoint  = 0
        self.RightPoint = 0

        init_window(self.ScreenWidth, self.ScreenHeight, self.GameTitle)
        init_audio_device()

        self.HitSound = load_sound("./hitSound.wav")
        self.Music    = load_music_stream("./music.mp3")
        self.Point    = load_sound("./point.wav")

        play_music_stream(self.Music)

        self.GameOver = False
        self.PlayerWin = ""

        # load things here!

    def GameUpdate(self):
        if (self.GameOver):
            self.LeftPoint = self.RightPoint = 0
            self.LeftPad   = Rectangle(10,  self.ScreenHeight/2-75, 10, 150)
            self.RightPad  = Rectangle(980, self.ScreenHeight/2-75, 10, 150)
            if (is_key_pressed(KEY_R)):
                self.GameOver = False
        else:
            if (self.LeftPoint == 5):
                self.PlayerWin = "Left Player Win"
                self.GameOver  = True
            elif (self.RightPoint == 5):
                self.PlayerWin = "Right Player Win"
                self.GameOver  = True

            self.BALLSpeed += 10 * get_frame_time()
            update_music_stream(self.Music)

            # Move Left Paddle
            if (is_key_down(KEY_W)):
                if (self.LeftPad.y > 0):
                    self.LeftPad.y -= 200 * get_frame_time()
            elif (is_key_down(KEY_S)):
                if (self.LeftPad.y < self.ScreenHeight-150):
                    self.LeftPad.y += 200 * get_frame_time()

            # Move Right Paddle
            if (is_key_down(KEY_UP)):
                if (self.RightPad.y > 0):
                    self.RightPad.y -= 200 * get_frame_time()
            elif (is_key_down(KEY_DOWN)):
                if (self.RightPad.y < self.ScreenHeight-150):
                    self.RightPad.y += 200 * get_frame_time()

            if (self.BALL.x < 0):
                self.BALL.x = self.ScreenWidth  / 2 - 15
                self.BALL.y = self.ScreenHeight / 2 - 15
                self.RightPoint += 1
                self.BALLSpeed = 200
            elif (self.BALL.x > self.ScreenWidth-15):
                self.BALL.x = self.ScreenWidth  / 2 - 15
                self.BALL.y = self.ScreenHeight / 2 - 15
                self.LeftPoint += 1
                self.BALLSpeed = 200
            
            # Point +1 Sound
            self.LeftEndAreaHit  = check_collision_recs(self.LeftEndArea,  self.BALL)
            self.RightEndAreaHit = check_collision_recs(self.RightEndArea, self.BALL)

            if (self.LeftEndAreaHit or self.RightEndAreaHit):
                play_sound(self.Point)

            # Paddle Players Hit
            self.LeftPad_Hit   = check_collision_recs(self.LeftPad, self.BALL)
            self.RightPad_Hit  = check_collision_recs(self.RightPad, self.BALL)

            if (self.LeftPad_Hit):
                play_sound(self.HitSound)
                self.LeftHit = True
                if (is_key_down(KEY_W)):
                    self.keyW = True
                elif (is_key_down(KEY_S)):
                    self.keyS = True
                else:
                    self.keyW = self.keyS = False
                    self.UpHit = self.DownHit = False

            elif (self.RightPad_Hit):
                play_sound(self.HitSound)
                self.LeftHit = False
                if (is_key_down(KEY_UP)):
                    self.keyW = True
                elif (is_key_down(KEY_DOWN)):
                    self.keyS = True
                else:
                    self.keyW = self.keyS = False
                    self.UpHit = self.DownHit = False

            self.TopBAR_Hit    = check_collision_recs(self.TopBAR, self.BALL)
            self.BottomBAR_Hit = check_collision_recs(self.BottomBAR, self.BALL)

            if (self.TopBAR_Hit):
                play_sound(self.HitSound)
                self.UpHit = True
                self.DownHit = False
                self.keyW = self.keyS = False
            elif (self.BottomBAR_Hit):
                play_sound(self.HitSound)
                self.UpHit = False
                self.DownHit = True
                self.keyW = self.keyS = False

            if (self.LeftHit):
                self.BALL.x += self.BALLSpeed * get_frame_time()
            else:
                self.BALL.x -= self.BALLSpeed * get_frame_time()
            
            # if left paddle hit and you press w or s
            if (self.keyW):
                self.BALL.y -= self.BALLSpeed * get_frame_time()
            elif (self.keyS):
                self.BALL.y += self.BALLSpeed * get_frame_time()
            # if hit top bar or bottom bar
            elif (self.UpHit):
                self.debug = "Up Hit True"
                self.BALL.y += self.BALLSpeed * get_frame_time()
            elif (self.DownHit):
                self.debug = "Down Hit True"
                self.BALL.y -= self.BALLSpeed * get_frame_time()


    def GameDraw(self):
        if (self.GameOver):
            draw_text(self.PlayerWin, 10, 10, 30, self.Color.GPurple5 )
            draw_text("Press R Play Again!!", self.ScreenWidth/2-200, self.ScreenHeight/2, 60, self.Color.GPurple5)
        else:
            draw_rectangle(
                self.LeftPad.x, self.LeftPad.y, 
                self.LeftPad.width, self.LeftPad.height, self.Color.GPurple4 )
            draw_rectangle(
                self.RightPad.x, self.RightPad.y, 
                self.RightPad.width, self.RightPad.height, self.Color.GPurple4 )
            draw_rectangle(
                self.TopBAR.x, self.TopBAR.y,
                self.TopBAR.width, self.TopBAR.height, self.Color.GPurple3 )
            draw_rectangle(
                self.BottomBAR.x, self.BottomBAR.y,
                self.BottomBAR.width, self.BottomBAR.height, self.Color.GPurple3 )
            draw_text(f" | Left Player: {self.LeftPoint} | Right Player: {self.RightPoint} | ", 240, 10, 30, self.Color.GPurple5)
            draw_rectangle(
                self.BALL.x, self.BALL.y,
                self.BALL.width, self.BALL.height, self.Color.GPurple3 )
            draw_fps(10, 10)

    def UnloadALL(self):
        for i in (self.Point, self.HitSound):
            unload_sound(i)
        unload_music_stream(self.Music)
        close_audio_device()

    def GameLoop(self):
        set_target_fps(60)
        while (not window_should_close()):
            self.GameUpdate()
            begin_drawing()
            clear_background(self.Color.GPurple0)
            self.GameDraw()
            end_drawing()
        self.UnloadALL()
        close_window()

if __name__ == "__main__":
    GC = SimpleGame()
    GC.GameLoop()
