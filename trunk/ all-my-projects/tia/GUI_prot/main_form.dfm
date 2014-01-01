object MainForm: TMainForm
  Left = 210
  Top = 129
  Width = 631
  Height = 345
  Caption = 'MainForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LText1: TLabel
    Left = 8
    Top = 72
    Width = 136
    Height = 13
    Caption = #1044#1072#1085#1085#1099#1077' '#1089' '#1058#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1072' = '
  end
  object LTenzoSpeed: TLabel
    Left = 144
    Top = 72
    Width = 24
    Height = 13
    Caption = 'none'
  end
  object Button1: TButton
    Left = 24
    Top = 24
    Width = 161
    Height = 25
    Caption = #1057#1086#1077#1076#1080#1085#1077#1085#1080#1077' '#1089' '#1087#1088#1090#1086#1090#1080#1087#1086#1084
    TabOrder = 0
    OnClick = Button1Click
  end
  object TrackBar1: TTrackBar
    Left = 176
    Top = 128
    Width = 150
    Height = 45
    Max = 100
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 1
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
  object TestTimer: TTimer
    Interval = 10
    OnTimer = TestTimerTimer
    Left = 296
    Top = 40
  end
  object SpeedMeterTimer: TTimer
    OnTimer = SpeedMeterTimerTimer
    Left = 536
    Top = 40
  end
end
