object ChartForm: TChartForm
  Left = 762
  Top = 238
  Width = 637
  Height = 542
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
    Left = 184
    Top = 352
    Width = 41
    Height = 16
    Caption = 'Label1'
  end
  object Chart1: TChart
    Left = 152
    Top = 8
    Width = 400
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
  end
end
