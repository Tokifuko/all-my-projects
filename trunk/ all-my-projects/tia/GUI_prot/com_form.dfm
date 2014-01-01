object ComForm: TComForm
  Left = 332
  Top = 163
  Width = 392
  Height = 450
  Caption = 'ComForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
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
    Left = 0
    Top = 168
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
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 393
    Width = 376
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
end
