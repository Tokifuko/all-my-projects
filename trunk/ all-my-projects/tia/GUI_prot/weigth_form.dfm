object WeightForm: TWeightForm
  Left = 870
  Top = 117
  Width = 739
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
  object Chart1: TChart
    Left = 0
    Top = 0
    Width = 705
    Height = 298
    Title.Text.Strings = (
      #1044#1072#1085#1085#1099#1077' '#1089' '#1040#1062#1055' / '#1042#1077#1089)
    View3D = False
    TabOrder = 0
    object CalibrSeries: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Title = 'CalibrSeries'
      LinePen.Color = clRed
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
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
      LinesPen.Color = clRed
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
      object TeeFunction1: TCustomTeeFunction
        Period = 1
        NumPoints = 100
      end
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
  end
  object TrackBar2: TTrackBar
    Left = 664
    Top = 360
    Width = 45
    Height = 217
    Max = 100
    Orientation = trVertical
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 3
    TickMarks = tmBottomRight
    TickStyle = tsAuto
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
  end
end
