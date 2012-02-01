object Form1: TForm1
  Left = 302
  Top = 140
  Width = 1305
  Height = 778
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Label1: TLabel
    Left = 88
    Top = 376
    Width = 55
    Height = 16
    Caption = 'ID '#1082#1072#1088#1090#1099
  end
  object Label2: TLabel
    Left = 280
    Top = 376
    Width = 169
    Height = 16
    Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1100#1073' '#1074#1080#1076#1080#1086' ('#1089#1077#1082')'
  end
  object Label3: TLabel
    Left = 560
    Top = 376
    Width = 88
    Height = 16
    Caption = #1055#1091#1090#1100' '#1082' '#1092#1072#1081#1083#1091
  end
  object lComChoise: TLabel
    Left = 56
    Top = 72
    Width = 73
    Height = 16
    Caption = 'lComChoise'
  end
  object lCurCardID: TLabel
    Left = 56
    Top = 488
    Width = 192
    Height = 22
    Caption = #1050#1072#1088#1090#1072' '#1085#1077' '#1085#1072#1081#1076#1077#1085#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object lCurVideoLength: TLabel
    Left = 280
    Top = 488
    Width = 161
    Height = 24
    Caption = #1050#1072#1088#1090#1072' '#1085#1077' '#1085#1072#1081#1076#1077#1085#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lCurCardFilePach: TLabel
    Left = 544
    Top = 488
    Width = 161
    Height = 24
    Caption = #1050#1072#1088#1090#1072' '#1085#1077' '#1085#1072#1081#1076#1077#1085#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object lBSPlayerPach: TLabel
    Left = 56
    Top = 632
    Width = 345
    Height = 16
    Caption = 'C:\Program Files (x86)\Webteh\BSplayerPro\bsplayer.exe'
  end
  object lPshFile: TLabel
    Left = 56
    Top = 680
    Width = 367
    Height = 16
    Caption = 'C:\AMV\psi\03605.kyle_m.Siar_Mortal-Slonik.amvnews.ru.mp4'
  end
  object ListBox1: TListBox
    Left = 56
    Top = 128
    Width = 889
    Height = 233
    ItemHeight = 16
    TabOrder = 0
  end
  object Edit1: TEdit
    Left = 64
    Top = 400
    Width = 121
    Height = 24
    TabOrder = 1
    Text = '123456'
  end
  object Edit2: TEdit
    Left = 280
    Top = 400
    Width = 121
    Height = 24
    TabOrder = 2
    Text = '90'
  end
  object Edit3: TEdit
    Left = 472
    Top = 400
    Width = 265
    Height = 24
    TabOrder = 3
    Text = 'C:\1.avi'
  end
  object btAddRecord: TButton
    Left = 968
    Top = 400
    Width = 153
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    TabOrder = 4
    OnClick = btAddRecordClick
  end
  object btDelRecord: TButton
    Left = 968
    Top = 128
    Width = 161
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    TabOrder = 5
    OnClick = btDelRecordClick
  end
  object btSaveData: TButton
    Left = 968
    Top = 184
    Width = 161
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
    TabOrder = 6
    OnClick = btSaveDataClick
  end
  object btLoadData: TButton
    Left = 968
    Top = 216
    Width = 169
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
    TabOrder = 7
    OnClick = btLoadDataClick
  end
  object cbPort: TComboBox
    Left = 56
    Top = 40
    Width = 145
    Height = 24
    ItemHeight = 16
    TabOrder = 8
    OnDropDown = cbPortDropDown
  end
  object btOpenPort: TButton
    Left = 224
    Top = 40
    Width = 137
    Height = 25
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1087#1086#1088#1090
    TabOrder = 9
    OnClick = btOpenPortClick
  end
  object btClosePort: TButton
    Left = 224
    Top = 72
    Width = 137
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100' '#1087#1086#1088#1090
    TabOrder = 10
    OnClick = btClosePortClick
  end
  object btGetCardID: TButton
    Left = 56
    Top = 440
    Width = 169
    Height = 25
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' '#1085#1086#1084#1077#1088' '#1082#1072#1088#1090#1099
    TabOrder = 11
    OnClick = btGetCardIDClick
  end
  object mLog: TMemo
    Left = 56
    Top = 528
    Width = 961
    Height = 89
    Lines.Strings = (
      #1083#1086#1075' '#1089#1086#1086#1073#1097#1077#1085#1080#1081)
    TabOrder = 12
  end
  object cbStartPlay: TCheckBox
    Left = 904
    Top = 480
    Width = 201
    Height = 17
    Caption = #1053#1072#1095#1072#1090#1100' '#1074#1086#1089#1087#1088#1086#1080#1079#1074#1077#1076#1077#1085#1080#1077
    TabOrder = 13
  end
  object bfFindBSPlayer: TButton
    Left = 448
    Top = 624
    Width = 153
    Height = 25
    Caption = #1053#1072#1081#1090#1080' BSPlayer'
    TabOrder = 14
    OnClick = bfFindBSPlayerClick
  end
  object btFindVideoFile: TButton
    Left = 472
    Top = 440
    Width = 137
    Height = 25
    Caption = #1053#1072#1081#1090#1080' '#1074#1080#1076#1080#1086#1092#1072#1081#1083
    TabOrder = 15
    OnClick = btFindVideoFileClick
  end
  object btFindPshFile: TButton
    Left = 448
    Top = 672
    Width = 153
    Height = 25
    Caption = #1053#1072#1081#1090#1080' '#1055#1097#1097#1097' '#1092#1072#1081#1083
    TabOrder = 16
    OnClick = btFindPshFileClick
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 1000
    Top = 8
  end
  object Timer2: TTimer
    Interval = 800
    OnTimer = Timer2Timer
    Left = 936
    Top = 8
  end
  object odFindBSPlayer: TOpenDialog
    Left = 600
    Top = 624
  end
  object odFindVideoFile: TOpenDialog
    Left = 632
    Top = 440
  end
  object odFindPshFile: TOpenDialog
    Left = 600
    Top = 672
  end
  object Timer3: TTimer
    OnTimer = Timer3Timer
    Left = 880
    Top = 8
  end
end
