object WeightForm: TWeightForm
  Left = 870
  Top = 150
  Width = 924
  Height = 768
  Caption = 'WeightForm'
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
    Left = 16
    Top = 320
    Width = 213
    Height = 16
    Caption = #1058#1077#1082#1091#1097#1080#1077' '#1091#1089#1088#1077#1076#1085#1077#1085#1085#1099#1077' '#1076#1072#1085#1085#1099#1077' = '
  end
  object Label2: TLabel
    Left = 16
    Top = 352
    Width = 96
    Height = 16
    Caption = #1058#1077#1082#1091#1097#1080#1081' '#1074#1077#1089' = '
  end
  object Label3: TLabel
    Left = 672
    Top = 344
    Width = 17
    Height = 16
    Caption = #1075#1088'.'
  end
  object Label4: TLabel
    Left = 592
    Top = 344
    Width = 16
    Height = 16
    Caption = #1082#1075'.'
  end
  object Label5: TLabel
    Left = 232
    Top = 320
    Width = 41
    Height = 16
    Caption = 'Label5'
  end
  object Label6: TLabel
    Left = 120
    Top = 352
    Width = 41
    Height = 16
    Caption = 'Label6'
  end
  object Label7: TLabel
    Left = 8
    Top = 432
    Width = 94
    Height = 16
    Caption = #1044#1072#1085#1085#1099#1077' '#1089' '#1040#1062#1055':'
  end
  object Label8: TLabel
    Left = 8
    Top = 464
    Width = 120
    Height = 64
    Caption = 'NON'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 376
    Top = 544
    Width = 24
    Height = 16
    Caption = #1042#1077#1089
  end
  object Label10: TLabel
    Left = 736
    Top = 16
    Width = 145
    Height = 16
    Caption = #1082#1072#1083#1080#1073#1088#1086#1074#1086#1095#1085#1099#1077' '#1090#1086#1095#1082#1080
  end
  object Chart1: TChart
    Left = 0
    Top = 0
    Width = 705
    Height = 298
    Title.Text.Strings = (
      #1044#1072#1085#1085#1099#1077' '#1089' '#1040#1062#1055' / '#1042#1077#1089)
    View3D = False
    TabOrder = 0
    PrintMargins = (
      15
      29
      15
      29)
    object CalibrSeries: THorizLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Shadow.Color = 8487297
      Marks.Style = smsPointIndex
      Marks.Visible = True
      Title = 'CalibrSeries'
      LinePen.Color = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      TreatNulls = tnIgnore
      XValues.Name = 'X'
      XValues.Order = loNone
      YValues.Name = 'Y'
      YValues.Order = loAscending
    end
    object CurrentPointSeries: TMyPointSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Title = 'CurrentPointSeries'
      ClickableLine = False
      Pointer.Draw3D = False
      Pointer.InflateMargins = True
      Pointer.Style = psDiamond
      Pointer.Visible = True
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
      LinesPen.Color = 4227072
    end
    object CurrentDataSeries: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      SeriesColor = clGreen
      Title = 'CurrentDataSeries'
      LinePen.Color = clGreen
      TreatNulls = tnDontPaint
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object btChWeigth: TButton
    Left = 200
    Top = 392
    Width = 147
    Height = 25
    Caption = #1059#1090#1086#1095#1085#1080#1090#1100' '#1074#1077#1089
    TabOrder = 1
    OnClick = btChWeigthClick
  end
  object TrackBar1: TTrackBar
    Left = 584
    Top = 360
    Width = 45
    Height = 217
    Max = 70
    Orientation = trVertical
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 2
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
  object TrackBar2: TTrackBar
    Left = 664
    Top = 360
    Width = 45
    Height = 217
    Max = 20
    Orientation = trVertical
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 3
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar2Change
  end
  object Button1: TButton
    Left = 424
    Top = 392
    Width = 99
    Height = 25
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 4
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 312
    Top = 456
    Width = 241
    Height = 72
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    Text = '0'
    OnExit = Edit1Exit
  end
  object btsaveToFile: TButton
    Left = 16
    Top = 576
    Width = 137
    Height = 25
    Caption = #1089#1086#1093#1088#1072#1085#1080#1090#1100' '#1074' '#1092#1072#1081#1083
    TabOrder = 6
    OnClick = btsaveToFileClick
  end
  object eFileNameEdit: TEdit
    Left = 16
    Top = 616
    Width = 497
    Height = 24
    TabOrder = 7
    Text = 'eFileNameEdit'
  end
  object btOpenDialog: TButton
    Left = 528
    Top = 616
    Width = 41
    Height = 25
    Caption = '......'
    TabOrder = 8
    OnClick = btOpenDialogClick
  end
  object btLoadFromFile: TButton
    Left = 200
    Top = 576
    Width = 153
    Height = 25
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1080#1079' '#1092#1072#1081#1083#1072
    TabOrder = 9
    OnClick = btLoadFromFileClick
  end
  object Memo1: TMemo
    Left = 712
    Top = 40
    Width = 169
    Height = 553
    Lines.Strings = (
      '65077; 4,6')
    TabOrder = 10
  end
  object btApply: TButton
    Left = 712
    Top = 600
    Width = 153
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 11
    OnClick = btApplyClick
  end
  object btCancel: TButton
    Left = 712
    Top = 632
    Width = 153
    Height = 25
    Caption = #1059#1073#1088#1072#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
    TabOrder = 12
  end
  object OpenDialog1: TOpenDialog
    Left = 592
    Top = 608
  end
end
