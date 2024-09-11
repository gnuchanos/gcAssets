from raylibpy import *

class CurrentScene:
    def __init__(self) -> None:
        self.Logo     = 0
        self.Menu     = 1
        self.GamePlay = 2
        self.End      = 3

class GColors:
    def __init__(self) -> None:
        self.GPurple0 = Color(  16,  1,   36, 255 )
        self.GPurple1 = Color(  34,  2,   77, 255 )
        self.GPurple2 = Color(  49,  3,  110, 255 )
        self.GPurple3 = Color(  67,  5,  150, 255 )
        self.GPurple4 = Color(  86,  6,  194, 255 )
        self.GPurple5 = Color( 110, 10,  245, 255 )

class Button:
    def __init__(self, Text, Font, ButtonPositionX, ButtonPositionY, TextColor, ButtonColor) -> None:
        self.Text = Text
        self.Font = Font
        self.TextFontSize = 30
        self.TextColor = TextColor
        self.ButtonColor = ButtonColor
        self.Press = False
        self.gcolor = GColors()
        self.TextWidth  = measure_text_ex(self.Font, self.Text, 30, 1).x + 10
        self.TextHeight = measure_text_ex(self.Font, self.Text, 30, 1).y + 10
        self.ButtonRectangle = Rectangle(ButtonPositionX, ButtonPositionY, self.TextWidth, self.TextHeight)

    def DrawNow(self):
        draw_rectangle( 
            self.ButtonRectangle.x,  self.ButtonRectangle.y, 
            self.TextWidth, self.TextHeight, 
            self.ButtonColor )
        draw_text_ex(
            self.Font,
            self.Text,
            Vector2(
                self.ButtonRectangle.x+self.TextWidth/2-self.TextWidth/2+5,
                self.ButtonRectangle.y+self.TextHeight/2-self.TextHeight/2+5
            ),
            self.TextFontSize,
            1, self.TextColor)

    def PressButton(self, MousePosition):
        self.ButtonPress = False
        if (check_collision_point_rec(MousePosition, self.ButtonRectangle)):
            if (is_mouse_button_down(MOUSE_BUTTON_LEFT)):
                self.ButtonPress = True
                self.ButtonColor = self.gcolor.GPurple4
            else:
                self.ButtonColor = self.gcolor.GPurple3
        else:
            self.ButtonColor = self.gcolor.GPurple2

# maybe i can use one day but not today
class CheckBox:
    def __init__(self, PositionVector2=Vector2(400, 500), ScaleVector2=Vector2(50, 50), PressCheckButton=False) -> None:
        self.GColor = GColors()
        self.Color    = self.GColor.GPurple1
        self.Position = PositionVector2
        self.Scale    = ScaleVector2
        self.PressCheckButton    = PressCheckButton
        self.RectangleForClick = Rectangle(self.Position.x, self.Position.y, self.Scale.x, self.Scale.y)
        self.CheckColor    = self.GColor.GPurple1
        self.CheckScale    = Vector2(self.Scale.x/2,                      self.Scale.y/2)
        self.CheckPosition = Vector2(self.Position.x+self.CheckScale.x/2, self.Position.y+self.CheckScale.y/2)
    
    def PressCheck(self, MousePosition):
        if (check_collision_point_rec(MousePosition, self.RectangleForClick)):
            if (is_mouse_button_pressed(MOUSE_BUTTON_LEFT) and not self.PressCheckButton):
                self.PressCheckButton = True
                self.CheckColor = self.GColor.GPurple2
            elif (is_mouse_button_pressed(MOUSE_LEFT_BUTTON) and self.PressCheckButton):
                self.PressCheckButton = False
                self.CheckColor = self.GColor.GPurple1

    def DrawNow(self):
        draw_rectangle(self.Position.x,      self.Position.y,      self.Scale.x,      self.Scale.y,      self.Color)
        draw_rectangle(self.CheckPosition.x, self.CheckPosition.y, self.CheckScale.x, self.CheckScale.y, self.CheckColor)
# maybe i can use one day but not today


class _2DPlayer:
    def __init__(self, ScreenWidth, ScreenHeight) -> None:
        self.ScreenWidth = ScreenWidth
        self.ScreenHeight = ScreenHeight

        self.PlayerBodyScale = Vector2( 200, 25 )
        self.PlayerPosition = Vector2( self.ScreenWidth/2-self.PlayerBodyScale.x/2, self.ScreenHeight-self.PlayerBodyScale.y-10 )
        self.PlayerBody2D = Rectangle( self.PlayerPosition.x, self.PlayerPosition.y, self.PlayerBodyScale.x, self.PlayerBodyScale.y )
        self.PlayerBodyColor = GColors().GPurple5

    def MovePlayer(self):
        if (is_key_down(KEY_LEFT)) or (is_key_down(KEY_A)):
            if (self.PlayerBody2D.x > 10):
                self.PlayerBody2D.x -= 200 * get_frame_time()
        if (is_key_down(KEY_D)) or (is_key_down(KEY_RIGHT)):
            if (self.PlayerBody2D.x+self.PlayerBody2D.width+10 < self.ScreenWidth):
                self.PlayerBody2D.x += 200 * get_frame_time()

    def DrawNow(self):
        draw_rectangle(self.PlayerBody2D.x, self.PlayerBody2D.y-5, self.PlayerBody2D.width, self.PlayerBody2D.height, self.PlayerBodyColor)


class GE:
    def __init__(self) -> None:
        self.ScreenWidth = 1000
        self.ScreenHeight = 600
        self.GameTitle = "Game Title UwU"
        set_config_flags(FLAG_MSAA_4X_HINT)
        init_window(self.ScreenWidth, self.ScreenHeight, self.GameTitle)
        init_audio_device()

        # CLASS
        self.SceneList = CurrentScene()
        self.ColorList = GColors()
        # CLASS

        # Settings
        self.MousePosition = Vector2(0, 0)
        set_exit_key(KEY_NULL)
        self.ShowMouse = True
        self.CurrentScene = self.SceneList.Logo
        self.LogoTimer = 2
        self.FONT = load_font("./Sans.ttf")
        # Settings

        # Menu
        self.Logo = load_texture("./logo.png")
        self.StartButton     = Button ( "Start Game", self.FONT, 100, 100, self.ColorList.GPurple5, self.ColorList.GPurple1 )
        self.OptionsButton   = Button( "Options Window", self.FONT, 45, 150, self.ColorList.GPurple5, self.ColorList.GPurple1 )
        # Menu

        # Default
        self.BackGroundImage = load_texture(file_name="./bg.png")
        # Default

        # This Is Can Change Every Game
        self.Point = 0
        self.Live  = 3
        self.PointAndLive = f" | Point:{self.Point} | Lives:{self.Live} | "
        self.PointAndLiveWidth = measure_text_ex(self.FONT, self.PointAndLive, 30, 1)

        self.Player = _2DPlayer(self.ScreenWidth, self.ScreenHeight)
        self.BALL = Rectangle(self.ScreenWidth/2-10, self.ScreenHeight/2+50, 20, 20)

        self.LeftWall  = Rectangle(0, 0, 10, self.ScreenHeight)
        self.RightWall = Rectangle(self.ScreenWidth-10, 0, 10, self.ScreenHeight)
        self.TopWall   = Rectangle(0, 0, self.ScreenWidth, 10)
        self.EndArea   = Rectangle(0, self.ScreenHeight-10, self.ScreenWidth, 10)

        self.Bricks_Level0 = {}
        self.MaxRow = 30
        self.MaxColumn = 10
        for i in range(0, self.MaxRow):
            self.Bricks_Level0[i] = {}
            for a in range(0, self.MaxColumn):
                self.Bricks_Level0[i][a] = {}
                self.Bricks_Level0[i][a]['b']  = Rectangle(55+(30*i), 50+20*a, 25, 10)
                self.Bricks_Level0[i][a]["bc"] = GColors().GPurple5
                self.Bricks_Level0[i][a]["bd"] = True

        self.TopBarHit   = False
        self.LeftBarHit  = False
        self.RightBarHit = False
        self.PaddleHit   = False
        self.BrickHit    = False
        self.EndAreaHit  = False

        self.LeftHit        = False
        self.RightHit       = False
        self.DownHit        = False
        self.TopHit         = True
        self.PlayerHit      = False
        self.BrickActiveHit = False

        # this is idea
        self.BALL_Power = False
        # This Is Can Change Every Game

        # Sounds
        self.HitsSound    = load_sound("./hitSound.wav")
        self.Music        = load_music_stream("./music.mp3")
        self.OutSideSound = load_sound("./point.wav")

        play_music_stream(self.Music)

    def Update(self):
        self.MousePosition = get_mouse_position()

        update_music_stream(self.Music)

        if (is_key_pressed(KEY_ESCAPE) and self.ShowMouse):
            disable_cursor()
            self.ShowMouse = False

        elif (is_key_pressed(KEY_ESCAPE) and not self.ShowMouse):
            enable_cursor()
            self.ShowMouse = True

        if   (self.CurrentScene == self.SceneList.Logo):
            if (self.LogoTimer > 0):
                self.LogoTimer -= get_frame_time()
            else:
                self.CurrentScene = self.SceneList.Menu

        elif (self.CurrentScene == self.SceneList.Menu):
            self.StartButton.PressButton(self.MousePosition)
            self.OptionsButton.PressButton(self.MousePosition)
            if (self.StartButton.ButtonPress):
                self.CurrentScene = self.SceneList.GamePlay
            elif (self.OptionsButton.ButtonPress):
                pass

        elif (self.CurrentScene == self.SceneList.GamePlay):
            self.Player.MovePlayer()

            self.TopBarHit   = check_collision_recs(self.TopWall,                self.BALL)
            self.LeftBarHit  = check_collision_recs(self.LeftWall,               self.BALL)
            self.RightBarHit = check_collision_recs(self.RightWall,              self.BALL)
            self.PaddleHit   = check_collision_recs(self.Player.PlayerBody2D,    self.BALL)
            self.EndAreaHit  = check_collision_recs(self.EndArea,                self.BALL)

            if self.TopBarHit:
                play_sound(self.HitsSound)
                self.TopHit = True
                self.PlayerHit = self.BrickActiveHit  = False

            elif self.LeftBarHit:
                play_sound(self.HitsSound)
                self.LeftHit = True
                self.RightHit = False

            elif self.RightBarHit:
                play_sound(self.HitsSound)
                self.RightHit = True
                self.LeftHit = False

            elif self.PaddleHit:
                play_sound(self.HitsSound)
                self.PlayerHit = True
                self.BrickActiveHit = False
                if (is_key_down(KEY_A)):
                    self.TopHit = self.LeftHit = self.BrickActiveHit  = False
                    self.RightHit = True
                elif (is_key_down(KEY_D)):
                    self.TopHit = self.RightHit = self.BrickActiveHit  = False
                    self.LeftHit  = True
                else:
                    self.TopHit = self.LeftHit = self.RightHit = self.BrickActiveHit  = False

            elif self.EndAreaHit:
                play_sound(self.OutSideSound)
                self.BALL.x = self.ScreenWidth/2-10
                self.BALL.y = self.ScreenHeight/2+50
                self.LeftHit = self.RightHit = self.BrickActiveHit = False
                if (self.Live != 1):
                    self.Live -= 1
                else:
                    self.CurrentScene = self.SceneList.End 
                self.PointAndLive = f" | Point:{self.Point} | Lives:{self.Live} | "

            for i in range(0, self.MaxRow):
                for a in range(0, self.MaxColumn):
                    if self.Bricks_Level0[i][a]["bd"]:
                        self.BrickHit = check_collision_recs(self.Bricks_Level0[i][a]['b'], self.BALL)
                        if self.BrickHit:
                            play_sound(self.HitsSound)
                            self.Bricks_Level0[i][a]["bd"] = False
                            self.BrickActiveHit = True
                            
                            self.Point += get_random_value(10, 1000)
                            self.PointAndLive = f" | point:{self.Point} | lives:{self.Live} | "
                            self.PointAndLiveWidth = measure_text_ex(self.FONT, self.PointAndLive, 30, 1)
                            break

            if (self.TopHit):
                self.BALL.y += 200 * get_frame_time()

                if (self.LeftHit):
                    self.BALL.x += 200 * get_frame_time()
                elif (self.RightHit):
                    self.BALL.x -= 200 * get_frame_time()

            elif (self.PlayerHit):
                if (not self.BrickActiveHit):
                    self.BALL.y -= 200 * get_frame_time()
                    if (self.LeftHit):
                        self.BALL.x += 200 * get_frame_time()
                    elif (self.RightHit):
                        self.BALL.x -= 200 * get_frame_time()
                else:
                    self.BALL.y += 200 * get_frame_time()
                    if (self.LeftHit):
                        self.BALL.x += 200 * get_frame_time()
                    elif (self.RightHit):
                        self.BALL.x -= 200 * get_frame_time()

            elif (self.BrickActiveHit):
                self.BALL.y += 200 * get_frame_time()

        elif (self.CurrentScene == self.SceneList.End):
            if (is_key_pressed(KEY_R)):
                self.LogoTimer = 2
                self.Live = 3
                self.Point = 0
                self.CurrentScene = self.SceneList.Logo

    def DrawObject(self):
        if   (self.CurrentScene == self.SceneList.Logo):
            draw_texture(self.BackGroundImage, 0, 0, WHITE)

        elif (self.CurrentScene == self.SceneList.Menu):
            draw_texture(self.Logo, 600, 200, WHITE)

        elif (self.CurrentScene == self.SceneList.GamePlay):
            for i in range(0, self.MaxRow):
                for a in range(0, self.MaxColumn):
                    if self.Bricks_Level0[i][a]["bd"]:
                        draw_rectangle( 
                                       self.Bricks_Level0[i][a]['b'].x, self.Bricks_Level0[i][a]['b'].y, 
                                       self.Bricks_Level0[i][a]['b'].width, self.Bricks_Level0[i][a]['b'].height, 
                                       self.Bricks_Level0[i][a]["bc"] )
            self.Player.DrawNow()
            draw_rectangle(self.BALL.x, self.BALL.y, self.BALL.width, self.BALL.height, self.ColorList.GPurple3)

            draw_rectangle(self.LeftWall.x, self.LeftWall.y, self.LeftWall.width, self.LeftWall.height, self.ColorList.GPurple3)
            draw_rectangle(self.RightWall.x, self.RightWall.y, self.RightWall.width, self.RightWall.height, self.ColorList.GPurple3)
            draw_rectangle(self.TopWall.x, self.TopWall.y, self.TopWall.width, self.TopWall.height, self.ColorList.GPurple4)
            draw_rectangle(self.EndArea.x, self.EndArea.y, self.EndArea.width, self.EndArea.height, self.ColorList.GPurple4)

        elif (self.CurrentScene == self.SceneList.End):
            pass

    def DrawUI(self):
        if   (self.CurrentScene == self.SceneList.Logo):
            pass

        elif (self.CurrentScene == self.SceneList.Menu):
            self.StartButton.DrawNow()

        elif (self.CurrentScene == self.SceneList.GamePlay):
            draw_text(self.PointAndLive, self.ScreenWidth/2-self.PointAndLiveWidth.x/2, 15, 30, self.ColorList.GPurple4)

        elif (self.CurrentScene == self.SceneList.End):
            draw_text("Press R to Play Again!", 10, 10, 30, self.ColorList.GPurple5);
            draw_text("Game Over", self.ScreenWidth/2-200, self.ScreenHeight/2, 60, self.ColorList.GPurple5)

    def GAME(self, ShowFPS=True):
        set_target_fps(60)
        while (not window_should_close()):
            self.Update()
            begin_drawing()
            clear_background(self.ColorList.GPurple0)
            self.DrawObject()
            self.DrawUI()
            if (ShowFPS):
                draw_rectangle(0, self.ScreenHeight-35, 90, 35, self.ColorList.GPurple2)
                draw_fps(10, self.ScreenHeight-25)
            end_drawing()


        # Unload ALL HERE
        for i in (self.HitsSound, self.OutSideSound):
            unload_sound(i)
        unload_music_stream(self.Music)
        close_audio_device()
        unload_texture(self.BackGroundImage)
        unload_texture(self.Logo)
        close_window()

if __name__ == "__main__":
    gc = GE()
    gc.GAME()
