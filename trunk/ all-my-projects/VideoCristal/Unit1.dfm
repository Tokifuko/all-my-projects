object Form1: TForm1
  Left = 305
  Top = 567
  Width = 1305
  Height = 674
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
    Left = 112
    Top = 528
    Width = 55
    Height = 16
    Caption = 'ID '#1082#1072#1088#1090#1099
  end
  object Label2: TLabel
    Left = 296
    Top = 536
    Width = 169
    Height = 16
    Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1100#1073' '#1074#1080#1076#1080#1086' ('#1089#1077#1082')'
  end
  object Label3: TLabel
    Left = 576
    Top = 536
    Width = 88
    Height = 16
    Caption = #1055#1091#1090#1100' '#1082' '#1092#1072#1081#1083#1091
  end
  object Button1: TButton
    Left = 272
    Top = 88
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object ListBox1: TListBox
    Left = 56
    Top = 216
    Width = 889
    Height = 233
    ItemHeight = 16
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 96
    Top = 552
    Width = 121
    Height = 24
    TabOrder = 2
    Text = '123456'
  end
  object Edit2: TEdit
    Left = 296
    Top = 560
    Width = 121
    Height = 24
    TabOrder = 3
    Text = '90'
  end
  object Edit3: TEdit
    Left = 568
    Top = 560
    Width = 121
    Height = 24
    TabOrder = 4
    Text = 'C:\1.avi'
  end
  object btAddRecord: TButton
    Left = 768
    Top = 560
    Width = 153
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    TabOrder = 5
    OnClick = btAddRecordClick
  end
  object btDelRecord: TButton
    Left = 968
    Top = 240
    Width = 161
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    TabOrder = 6
    OnClick = btDelRecordClick
  end
  object btSaveData: TButton
    Left = 984
    Top = 320
    Width = 137
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
    TabOrder = 7
    OnClick = btSaveDataClick
  end
  object btLoadData: TButton
    Left = 1008
    Top = 368
    Width = 145
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1076#1072#1085#1085#1099#1077
    TabOrder = 8
    OnClick = btLoadDataClick
  end
  object cbPort: TComboBox
    Left = 536
    Top = 120
    Width = 145
    Height = 24
    ItemHeight = 16
    TabOrder = 9
    OnDropDown = cbPortDropDown
  end
end
