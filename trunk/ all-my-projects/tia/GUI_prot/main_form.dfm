object MainForm: TMainForm
  Left = 615
  Top = 328
  Width = 506
  Height = 242
  Caption = 'MainForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
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
  object Label1: TLabel
    Left = 224
    Top = 88
    Width = 132
    Height = 16
    Caption = #1086#1090#1089#1095#1077#1090#1086#1074'  '#1074' '#1089#1077#1082#1091#1085#1076#1091
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
    Left = 33
    Top = 142
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
    Left = 368
    Top = 48
    Width = 75
    Height = 25
    Caption = #1043#1088#1072#1092#1080#1082#1080
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 320
    Top = 120
    Width = 147
    Height = 25
    Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072' '#1074#1077#1089#1072
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 320
    Top = 160
    Width = 145
    Height = 25
    Caption = #1056#1072#1089#1095#1077#1090' '#1076#1072#1074#1083#1077#1085#1080#1103
    TabOrder = 4
    OnClick = Button4Click
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
    Left = 416
    Top = 16
  end
  object ProcessTimer: TTimer
    Interval = 100
    OnTimer = ProcessTimerTimer
    Left = 296
    Top = 8
  end
end
