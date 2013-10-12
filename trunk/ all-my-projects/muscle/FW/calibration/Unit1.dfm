object Form1: TForm1
  Left = 245
  Top = 192
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1056#1072#1073#1086#1090#1072' '#1089' COM-'#1087#1086#1088#1090#1086#1084' ('#1042#1077#1088#1089#1080#1103' 1 - TThread)'
  ClientHeight = 494
  ClientWidth = 1062
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 120
  TextHeight = 13
  object lCalipersData: TLabel
    Left = 672
    Top = 408
    Width = 218
    Height = 48
    Caption = 'lCalipersData'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 50
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 192
    Top = 416
    Width = 112
    Height = 48
    Caption = 'Label7'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 50
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 368
    Top = 416
    Width = 112
    Height = 48
    Caption = 'Label7'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 50
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 201
    Height = 169
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1087#1086#1088#1090#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 66
      Height = 13
      Caption = #1053#1086#1084#1077#1088' '#1087#1086#1088#1090#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 16
      Top = 72
      Width = 98
      Height = 13
      Caption = #1057#1082#1086#1088#1086#1089#1090#1100' '#1087#1077#1088#1077#1076#1072#1095#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object SpeedButton1: TSpeedButton
      Left = 16
      Top = 128
      Width = 105
      Height = 25
      AllowAllUp = True
      GroupIndex = 1
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1087#1086#1088#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Glyph.Data = {
        E6000000424DE60000000000000076000000280000000E0000000E0000000100
        0400000000007000000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        33003333333333333300300000000333330000B7B7B7B03333000B0B7B7B7B03
        33000BB0B7B7B7B033000FBB0000000033000BFB0B0B0B0333000FBFBFBFB003
        33000BFBFBF00033330030BFBF03333333003800008333333300333333333333
        33003333333333333300}
      ParentFont = False
      OnClick = SpeedButton1Click
    end
    object ComboBox1: TComboBox
      Left = 16
      Top = 40
      Width = 97
      Height = 21
      Style = csDropDownList
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ItemIndex = 0
      ParentFont = False
      TabOrder = 0
      Text = 'COM1'
      Items.Strings = (
        'COM1'
        'COM2')
    end
    object ComboBox2: TComboBox
      Left = 16
      Top = 88
      Width = 97
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      ItemIndex = 12
      ParentFont = False
      TabOrder = 1
      Text = '115200'
      Items.Strings = (
        '110'
        '300'
        '600'
        '1200'
        '2400'
        '4800'
        '9600'
        '14400'
        '19200'
        '38400'
        '56000'
        '57600'
        '115200')
    end
    object CheckBox1: TCheckBox
      Left = 144
      Top = 40
      Width = 49
      Height = 17
      Caption = 'DTR'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object CheckBox2: TCheckBox
      Left = 144
      Top = 80
      Width = 49
      Height = 17
      Caption = 'RTS'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = CheckBox2Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 184
    Width = 353
    Height = 201
    Caption = #1055#1077#1088#1077#1076#1072#1095#1072' '#1076#1072#1085#1085#1099#1093
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Label3: TLabel
      Left = 16
      Top = 24
      Width = 154
      Height = 13
      Caption = #1042#1074#1077#1076#1080#1090#1077' '#1076#1072#1085#1085#1099#1077' '#1076#1083#1103' '#1087#1077#1088#1077#1076#1072#1095#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 16
      Top = 72
      Width = 95
      Height = 13
      Caption = #1055#1088#1080#1085#1103#1090#1099#1077' '#1076#1072#1085#1085#1099#1077':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 16
      Top = 40
      Width = 209
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 254
      ParentFont = False
      TabOrder = 0
    end
    object Memo1: TMemo
      Left = 16
      Top = 88
      Width = 209
      Height = 97
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Lines.Strings = (
        #1083#1080#1085#1080#1103' 1'
        #1083#1080#1085#1080#1103' 2')
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object Button1: TButton
      Left = 240
      Top = 40
      Width = 89
      Height = 25
      Caption = #1055#1077#1088#1077#1076#1072#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button3: TButton
      Left = 240
      Top = 88
      Width = 89
      Height = 25
      Caption = #1054#1095#1080#1089#1090#1082#1072' '#1087#1086#1083#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = Button3Click
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 475
    Width = 1062
    Height = 19
    Panels = <
      item
        Width = 140
      end
      item
        Width = 85
      end
      item
        Width = 50
      end>
    SimplePanel = False
    SizeGrip = False
  end
  object GroupBox3: TGroupBox
    Left = 216
    Top = 8
    Width = 145
    Height = 169
    Caption = #1047#1072#1087#1080#1089#1100' '#1074' '#1092#1072#1081#1083
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    object Label5: TLabel
      Left = 16
      Top = 72
      Width = 60
      Height = 13
      Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 88
      Top = 72
      Width = 40
      Height = 13
      Caption = 'test.txt'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object CheckBox3: TCheckBox
      Left = 16
      Top = 40
      Width = 113
      Height = 17
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = CheckBox3Click
    end
  end
  object Chart1: TChart
    Left = 440
    Top = 8
    Width = 593
    Height = 385
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'TChart')
    View3D = False
    TabOrder = 4
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clGreen
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series3: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clYellow
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Button2: TButton
    Left = 56
    Top = 408
    Width = 75
    Height = 25
    Caption = 'Button2'
    TabOrder = 5
    OnClick = Button2Click
  end
end
