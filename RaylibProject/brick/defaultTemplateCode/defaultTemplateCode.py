from raylibpy import *
import numpy as npy

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
            self.ButtonRectangle.x, 
            self.ButtonRectangle.y, 
            self.TextWidth,
            self.TextHeight, 
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

class Slider_h:
    def __init__(self, LinePositionX= 50, LinePositionY=300, LineWidth=500, LineColor=GColors().GPurple2, SliderVAR=6) -> None:
        self.LinePositionX = LinePositionX
        self.LinePositionY = LinePositionY
        self.LineWidth = self.LinePositionX + LineWidth
        self.LineColor = LineColor
        self.GrabScale = Vector2(10, 10)
        self.GrabPosition = Vector2(self.LinePositionX - self.GrabScale.x / 2, self.LinePositionY - self.GrabScale.y / 2)
        self.GrabColor = GColors().GPurple4
        self.SliderGrabPress = False
        self.SliderVAR = SliderVAR
        self.Range_Start = 0
        self.Range_End = 100
        self.part = 10
        self.Value = npy.linspace(self.LinePositionX, self.LineWidth, self.part)
        self.GrabButtonRectangle_DontChange = Rectangle(self.GrabPosition.x, self.GrabPosition.y, self.GrabScale.x, self.GrabScale.y)
        self.gcolor = GColors()

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

class GE:
    def __init__(self) -> None:
        self.ScreenWidth = 1000
        self.ScreenHeight = 600
        self.GameTitle = "Game Title UwU"
        init_window(self.ScreenWidth, self.ScreenHeight, self.GameTitle)

        # CLASS
        self.SceneList = CurrentScene()
        self.ColorList = GColors()
        # CLASS

        # Settings
        self.MousePosition = Vector2(0, 0)
        set_exit_key(KEY_NULL)
        self.ShowMouse = False
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

    def Update(self):
        self.MousePosition = get_mouse_position()
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
            pass
        elif (self.CurrentScene == self.SceneList.End):
            pass

    def DrawObject(self):
        if   (self.CurrentScene == self.SceneList.Logo):
            draw_texture(self.BackGroundImage, 0, 0, WHITE)
        elif (self.CurrentScene == self.SceneList.Menu):
            draw_texture(self.Logo, 600, 200, WHITE)
        elif (self.CurrentScene == self.SceneList.GamePlay):
            draw_text("This is GamePlay Scene", 10, 10, 30, self.ColorList.GPurple5)
        elif (self.CurrentScene == self.SceneList.End):
            pass

    def DrawUI(self, ShowFPS=True):
        if   (self.CurrentScene == self.SceneList.Logo):
            pass
        elif (self.CurrentScene == self.SceneList.Menu):
            self.StartButton.DrawNow()
        elif (self.CurrentScene == self.SceneList.GamePlay):
            pass
        elif (self.CurrentScene == self.SceneList.End):
            pass
        if (ShowFPS):
            draw_rectangle(0, self.ScreenHeight-35, 90, 35, self.ColorList.GPurple2)
            draw_fps(10, self.ScreenHeight-25)

    def GAME(self):
        set_target_fps(60)
        while (not window_should_close()):
            self.Update()
            begin_drawing()
            clear_background(self.ColorList.GPurple0)
            self.DrawObject()
            self.DrawUI()
            end_drawing()
        # Unload ALL HERE
        unload_texture(self.BackGroundImage)
        close_window()

if __name__ == "__main__":
    gc = GE()
    gc.GAME()