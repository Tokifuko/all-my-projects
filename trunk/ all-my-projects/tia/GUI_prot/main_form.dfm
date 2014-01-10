object MainForm: TMainForm
  Left = 441
  Top = 299
  Width = 631
  Height = 345
  Caption = 'MainForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object LText1: TLabel
    Left = 10
    Top = 89
    Width = 171
    Height = 16
    Caption = #1044#1072#1085#1085#1099#1077' '#1089' '#1058#1077#1085#1079#1086#1076#1072#1090#1095#1080#1082#1072' = '
  end
  object LTenzoSpeed: TLabel
    Left = 177
    Top = 89
    Width = 30
    Height = 16
    Caption = 'none'
  end
  object Button1: TButton
    Left = 30
    Top = 30
    Width = 198
    Height = 30
    Caption = #1057#1086#1077#1076#1080#1085#1077#1085#1080#1077' '#1089' '#1087#1088#1090#1086#1090#1080#1087#1086#1084
    TabOrder = 0
    OnClick = Button1Click
  end
  object TrackBar1: TTrackBar
    Left = 217
    Top = 158
    Width = 184
    Height = 55
    Max = 100
    Min = 1
    Orientation = trHorizontal
    Frequency = 1
    Position = 50
    SelEnd = 0
    SelStart = 0
    TabOrder = 1
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
  object Button2: TButton
    Left = 488
    Top = 72
    Width = 75
    Height = 25
    Caption = #1043#1088#1072#1092#1080#1082#1080
    TabOrder = 2
    OnClick = Button2Click
  end
  object TestTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = TestTimerTimer
    Left = 296
    Top = 40
  end
  object SpeedMeterTimer: TTimer
    OnTimer = SpeedMeterTimerTimer
    Left = 536
    Top = 40
  end
  object ProcessTimer: TTimer
    Interval = 100
    OnTimer = ProcessTimerTimer
    Left = 416
    Top = 32
  end
end
