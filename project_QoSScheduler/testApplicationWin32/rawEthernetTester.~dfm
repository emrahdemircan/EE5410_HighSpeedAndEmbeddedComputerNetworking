object mainForm: TmainForm
  Left = 581
  Top = 341
  Width = 650
  Height = 500
  Caption = 'Raw Ethernet Tester'
  Color = clBtnFace
  Constraints.MaxHeight = 500
  Constraints.MaxWidth = 650
  Constraints.MinHeight = 500
  Constraints.MinWidth = 650
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 328
    Top = 0
    Width = 313
    Height = 217
    BevelInner = bvSpace
    BevelOuter = bvLowered
    TabOrder = 1
    object sendProgressBar: TProgressBar
      Left = 96
      Top = 56
      Width = 201
      Height = 17
      Min = 0
      Max = 1000000
      TabOrder = 0
    end
    object quitButton: TButton
      Left = 222
      Top = 80
      Width = 75
      Height = 25
      Caption = 'Quit'
      Enabled = False
      TabOrder = 1
      OnClick = quitButtonClick
    end
    object numOfMsgsTrackBar: TTrackBar
      Left = 2
      Top = 8
      Width = 303
      Height = 45
      LineSize = 10000
      Max = 1000000
      Min = 1
      Orientation = trHorizontal
      PageSize = 10000
      Frequency = 10000
      Position = 1
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = numOfMsgsTrackBarChange
    end
    object numOfMsgsEdit: TEdit
      Left = 12
      Top = 54
      Width = 81
      Height = 21
      Enabled = False
      TabOrder = 3
    end
    object sendButton: TButton
      Left = 144
      Top = 80
      Width = 75
      Height = 25
      Caption = 'Send'
      TabOrder = 4
      OnClick = sendButtonClick
    end
    object rawRcvdEdit: TLabeledEdit
      Left = 184
      Top = 116
      Width = 113
      Height = 21
      EditLabel.Width = 135
      EditLabel.Height = 13
      EditLabel.Caption = 'Raw Eth. Packets Received'
      LabelPosition = lpLeft
      LabelSpacing = 3
      ReadOnly = True
      TabOrder = 5
    end
  end
  object recvMemo: TMemo
    Left = 0
    Top = 224
    Width = 641
    Height = 241
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object interfaceListBox: TListBox
    Left = 0
    Top = 0
    Width = 321
    Height = 57
    ItemHeight = 13
    TabOrder = 2
    OnDblClick = interfaceListBoxDblClick
  end
  object Panel2: TPanel
    Left = 0
    Top = 64
    Width = 321
    Height = 153
    BevelInner = bvSpace
    BevelOuter = bvLowered
    TabOrder = 3
    object rawMaxLenSpinEdit: TCSpinEdit
      Left = 72
      Top = 40
      Width = 60
      Height = 22
      EditorEnabled = False
      Increment = 20
      MaxValue = 1500
      MinValue = 40
      TabOrder = 0
      Value = 240
    end
    object lengthLabel: TStaticText
      Left = 8
      Top = 43
      Width = 60
      Height = 17
      Caption = 'Max Length'
      TabOrder = 1
    end
    object addFlowButton: TButton
      Left = 240
      Top = 72
      Width = 75
      Height = 25
      Caption = 'Add Flow'
      TabOrder = 2
      OnClick = addFlowButtonClick
    end
    object etherTypeComboBox: TComboBox
      Left = 72
      Top = 8
      Width = 60
      Height = 22
      Style = csOwnerDrawFixed
      ItemHeight = 16
      ItemIndex = 0
      TabOrder = 3
      Text = '0x8800'
      Items.Strings = (
        '0x8800'
        '0x8801'
        '0x8802'
        '0x8803'
        '0x8804'
        '0x8805'
        '0x8806'
        '0x8807')
    end
    object StaticText2: TStaticText
      Left = 16
      Top = 10
      Width = 53
      Height = 17
      Caption = 'EtherType'
      TabOrder = 4
    end
    object flowsComboBox: TComboBox
      Left = 72
      Top = 113
      Width = 145
      Height = 22
      Style = csOwnerDrawFixed
      ItemHeight = 16
      TabOrder = 5
    end
    object StaticText3: TStaticText
      Left = 32
      Top = 116
      Width = 31
      Height = 17
      Caption = 'Flows'
      TabOrder = 6
    end
    object removeFlowButton: TButton
      Left = 240
      Top = 112
      Width = 75
      Height = 25
      Caption = 'Remove Flow'
      TabOrder = 7
      OnClick = removeFlowButtonClick
    end
    object recurrenceSpinEdit: TCSpinEdit
      Left = 256
      Top = 8
      Width = 60
      Height = 22
      EditorEnabled = False
      TabOrder = 8
      Value = 1
    end
    object StaticText4: TStaticText
      Left = 168
      Top = 11
      Width = 83
      Height = 17
      Caption = 'Recurrence / 64'
      TabOrder = 9
    end
  end
  object rawMinLenSpinEdit: TCSpinEdit
    Left = 256
    Top = 107
    Width = 60
    Height = 22
    EditorEnabled = False
    Increment = 20
    MaxValue = 1500
    MinValue = 40
    TabOrder = 4
    Value = 240
  end
  object StaticText1: TStaticText
    Left = 192
    Top = 110
    Width = 57
    Height = 17
    Caption = 'Min Length'
    TabOrder = 5
  end
end
