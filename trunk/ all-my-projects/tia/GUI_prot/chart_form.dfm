object ChartForm: TChartForm
  Left = 620
  Top = 678
  Width = 1119
  Height = 335
  Caption = 'ChartForm'
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
    Left = 216
    Top = 256
    Width = 41
    Height = 16
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 8
    Top = 256
    Width = 207
    Height = 16
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1090#1086#1095#1077#1082' '#1085#1072' '#1075#1088#1072#1092#1080#1082#1077' ='
  end
  object Chart1: TChart
    Left = 0
    Top = 0
    Width = 1089
    Height = 250
    AllowPanning = pmHorizontal
    Title.Text.Strings = (
      'TChart')
    Pages.AutoScale = True
    View3D = False
    TabOrder = 0
    PrintMargins = (
      15
      19
      15
      19)
    object Series1: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      LinePen.Color = clRed
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object SlideMedSeries: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Title = 'SlideMedSeries'
      LinePen.Color = clGreen
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object PseudoSlideMedSeries: TFastLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      SeriesColor = clBlue
      Title = 'PseudoSlideMedSeries'
      LinePen.Color = clBlue
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object btClear: TButton
    Left = 312
    Top = 256
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 1
    OnClick = btClearClick
  end
end
