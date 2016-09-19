VERSION 5.00
Object = "{FE0065C0-1B7B-11CF-9D53-00AA003C9CB6}#1.1#0"; "COMCT232.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmeditBitmap 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Frame editor"
   ClientHeight    =   8505
   ClientLeft      =   45
   ClientTop       =   360
   ClientWidth     =   9480
   Icon            =   "frmBitmap2.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   8505
   ScaleWidth      =   9480
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   8160
      TabIndex        =   28
      Top             =   3960
      Width           =   855
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   7800
      TabIndex        =   26
      Top             =   8040
      Width           =   1215
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Ok"
      Height          =   375
      Left            =   6600
      TabIndex        =   25
      Top             =   8040
      Width           =   1215
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Auto update Frame1"
      Height          =   375
      Left            =   7320
      TabIndex        =   22
      Top             =   2640
      Value           =   1  'Checked
      Width           =   1815
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   9240
      Top             =   5880
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame Ccode 
      Caption         =   "Ccode"
      Height          =   3495
      Left            =   240
      TabIndex        =   17
      Top             =   4920
      Width           =   5655
      Begin VB.CommandButton Command2 
         Caption         =   "bmp2txt"
         Height          =   375
         Left            =   3720
         TabIndex        =   24
         Top             =   3000
         Width           =   1215
      End
      Begin VB.CommandButton Command1 
         Caption         =   "txt2bmp"
         Height          =   375
         Left            =   2520
         TabIndex        =   23
         Top             =   3000
         Width           =   1215
      End
      Begin VB.TextBox Text1 
         Height          =   2655
         Left            =   120
         MultiLine       =   -1  'True
         TabIndex        =   18
         Top             =   240
         Width           =   5415
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Preview"
      Height          =   3015
      Left            =   6000
      TabIndex        =   15
      Top             =   4920
      Width           =   3165
      Begin VB.PictureBox pctPreview 
         Appearance      =   0  'Flat
         AutoRedraw      =   -1  'True
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   1755
         Left            =   120
         ScaleHeight     =   117
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   194
         TabIndex        =   16
         Top             =   360
         Width           =   2910
      End
   End
   Begin VB.TextBox txtY 
      Height          =   330
      Left            =   7920
      TabIndex        =   13
      Text            =   "28"
      Top             =   3480
      Width           =   495
   End
   Begin VB.TextBox txtX 
      Height          =   330
      Left            =   7920
      TabIndex        =   10
      Text            =   "72"
      Top             =   3120
      Width           =   495
   End
   Begin VB.PictureBox pctTemp 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFFF&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1815
      Left            =   5040
      ScaleHeight     =   121
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   113
      TabIndex        =   8
      Top             =   480
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.Frame Frame4 
      Caption         =   "Hexdata"
      Height          =   585
      Left            =   120
      TabIndex        =   6
      Top             =   4320
      Width           =   9015
      Begin VB.TextBox txtHex 
         Height          =   285
         Left            =   120
         TabIndex        =   7
         Top             =   240
         Width           =   8655
      End
   End
   Begin VB.CommandButton cmdInvert 
      Caption         =   "Invert"
      Height          =   375
      Left            =   7440
      TabIndex        =   5
      Top             =   720
      Width           =   1455
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "Clear"
      Height          =   375
      Left            =   7440
      TabIndex        =   4
      Top             =   240
      Width           =   1455
   End
   Begin VB.Frame Frame3 
      Caption         =   "Bitmap's view"
      Height          =   3960
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   7005
      Begin VB.PictureBox pctBitmap 
         Appearance      =   0  'Flat
         AutoRedraw      =   -1  'True
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   3570
         Left            =   120
         ScaleHeight     =   238
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   433
         TabIndex        =   3
         Top             =   240
         Width           =   6495
      End
   End
   Begin VB.CommandButton cmdLoadBitmap 
      Caption         =   "Load from BMP"
      Height          =   375
      Left            =   7440
      TabIndex        =   1
      Top             =   1680
      Width           =   1455
   End
   Begin VB.CommandButton cmdSaveBMP 
      Caption         =   "Save to BMP"
      Height          =   375
      Left            =   7440
      TabIndex        =   0
      Top             =   1200
      Width           =   1455
   End
   Begin ComCtl2.UpDown scrX 
      Height          =   330
      Left            =   8520
      TabIndex        =   11
      Top             =   3120
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   582
      _Version        =   327681
      Value           =   72
      Max             =   96
      Min             =   1
      Enabled         =   -1  'True
   End
   Begin ComCtl2.UpDown scrY 
      Height          =   330
      Left            =   8520
      TabIndex        =   14
      Top             =   3480
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   582
      _Version        =   327681
      Value           =   28
      Max             =   65
      Min             =   1
      Enabled         =   -1  'True
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Insert"
      Height          =   375
      Left            =   6120
      TabIndex        =   29
      Top             =   8040
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Label Label4 
      Caption         =   "bmp name:"
      Height          =   255
      Left            =   7200
      TabIndex        =   27
      Top             =   3960
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Label4"
      Height          =   255
      Left            =   8760
      TabIndex        =   21
      Top             =   2280
      Width           =   615
   End
   Begin VB.Label Label45 
      Caption         =   "sizeof ( bitmap ) == "
      Height          =   255
      Left            =   7320
      TabIndex        =   20
      Top             =   2280
      Width           =   1335
   End
   Begin VB.Label lblCoord 
      Alignment       =   2  'Center
      Height          =   255
      Left            =   120
      TabIndex        =   19
      Top             =   4080
      Width           =   2895
   End
   Begin VB.Label Label3 
      Caption         =   "Y Size:"
      Height          =   255
      Left            =   7320
      TabIndex        =   12
      Top             =   3480
      Width           =   495
   End
   Begin VB.Label Label2 
      Caption         =   "X Size:"
      Height          =   255
      Left            =   7320
      TabIndex        =   9
      Top             =   3120
      Width           =   495
   End
End
Attribute VB_Name = "frmeditBitmap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit




Private Sub cmdClear_Click()
Dim i As Integer
    pctPreview.Cls
    pctBitmap.Cls
    pctBitmap.Line (0, 0)-(pctBitmap.ScaleWidth, pctBitmap.ScaleHeight), vbWhite, BF
    For i = 0 To pctBitmap.ScaleWidth Step 5
        pctBitmap.Line (i, 0)-(i, pctBitmap.ScaleHeight), vbBlack
    Next
    
    For i = 0 To pctBitmap.ScaleHeight Step 5
        pctBitmap.Line (0, i)-(pctBitmap.ScaleWidth, i), vbBlack
    Next
    pctBitmap_MouseUp 0, 0, 0, 0
End Sub

Private Sub cmdInvert_Click()
Dim i As Integer
Dim a As Integer
Dim X As Integer
Dim BinStr As String
Dim dummy As String
Dim WalkOffset As Integer
Dim CurrentRow As Integer
Dim CurrentCol As Integer
Dim Block As Integer
    
    WalkOffset = 1
    CurrentCol = 0
    Block = 0
    For i = 1 To txtX.Text * CInt(txtY.Text / 8 + 0.4999999)
        For a = 0 To 7
            If pctPreview.Point(CurrentCol * 2, a * 2 + Block * 2) = vbBlack Then
                pctPreview.Line (CurrentCol * 2, a * 2 + Block * 2)-(CurrentCol * 2 + 1, a * 2 + Block * 2 + 1), pctPreview.BackColor, BF
                DrawBitmapPoint CurrentCol + 1, a + Block + 1, vbWhite
            Else
                pctPreview.Line (CurrentCol * 2, a * 2 + Block * 2)-(CurrentCol * 2 + 1, a * 2 + Block * 2 + 1), vbBlack, BF
                DrawBitmapPoint CurrentCol + 1, a + Block + 1, vbBlack
            End If
        Next
        WalkOffset = WalkOffset + 8
        CurrentCol = CurrentCol + 1
        If CurrentCol > (txtX.Text - 1) Then
            CurrentCol = 0
            Block = Block + 8
        End If
    Next
    pctBitmap_MouseUp 0, 0, 0, 0
End Sub

Public Sub UpdateBitmap()
On Error Resume Next
Dim i As Integer
Dim a As Integer
Dim X As Integer
Dim BinStr As String
Dim dummy As String
Dim WalkOffset As Integer
Dim CurrentRow As Integer
Dim CurrentCol As Integer
Dim Block As Integer
BinStr = convert_hex2dual(txtHex.Text)
    

    ResizeBitmap txtX.Text, txtY.Text

    pctPreview.Cls
    pctTemp.Cls
    pctTemp.Width = txtX.Text * Screen.TwipsPerPixelX
    pctTemp.Height = txtY.Text * Screen.TwipsPerPixelY
    WalkOffset = 1
    CurrentCol = 0
    Block = 0
    For i = 1 To txtX.Text * CInt(txtY.Text / 8 + 0.49)
        
        dummy = Reverse(Mid(BinStr, WalkOffset, 8))
        For a = 0 To 7
            If Mid(dummy, a + 1, 1) = "1" Then
                pctPreview.Line (CurrentCol * 2, a * 2 + Block * 2)-(CurrentCol * 2 + 1, a * 2 + Block * 2 + 1), vbBlack, BF
                DrawBitmapPoint CurrentCol + 1, a + Block + 1, vbBlack
                pctTemp.PSet (CurrentCol, a + Block)
            End If
        Next
        WalkOffset = WalkOffset + 8
        CurrentCol = CurrentCol + 1
        If CurrentCol > (txtX.Text - 1) Then
            CurrentCol = 0
            Block = Block + 8
        End If
    Next
    
Label1 = "0x" & Hex(Len(txtHex.Text) / 2)
If Check1.Value = 1 Then
    Command2_Click
End If

End Sub

Private Sub cmdSaveBMP_Click()
On Error GoTo Done
Dim Lang As String
Dim ByteLen As Integer
Dim i  As Long
Dim LenNum As Long

    CommonDialog1.CancelError = True
    CommonDialog1.DialogTitle = "Browse for *.bmp"
    CommonDialog1.Filter = "Bitmap files|*.bmp|All Files|*.*"
    
Again:
    CommonDialog1.ShowSave
    
    If FileExists(CommonDialog1.FileName) Then
        If MsgBox("Really overwrite this file?", vbQuestion + vbYesNo) = vbNo Then GoTo Again
        Kill CommonDialog1.FileName
    End If
    
    SavePicture pctTemp.image, CommonDialog1.FileName
Done:
End Sub







Private Sub cmdLoadBitmap_Click()
On Error GoTo Done

    CommonDialog1.CancelError = True
    CommonDialog1.DialogTitle = "Browse for *.bmp"
    CommonDialog1.Filter = "Bitmap file|*.bmp|All Files|*.*"
Again:
    CommonDialog1.ShowOpen
    If Not FileExists(CommonDialog1.FileName) Then GoTo Again

    pctTemp.Picture = LoadPicture(CommonDialog1.FileName, , vbLPMonochrome)

Dim i As Integer
Dim a As Integer
Dim BinStr As String
Dim WalkOffset As Integer
Dim CurrentRow As Integer
Dim CurrentCol As Integer
Dim Block As Integer
Dim dummy As String

     scrX.Value = pctTemp.ScaleWidth
     scrY.Value = pctTemp.ScaleHeight
     txtX.Text = scrX.Value
     txtY.Text = scrY.Value
    txtHex.Text = ""
    WalkOffset = 1
    CurrentCol = 0
    Block = 0
    pctPreview.Cls
    pctTemp.Cls
        For i = 1 To CInt(txtX.Text) * CInt(txtY.Text / 8 + 0.49999999) '- 1
        For a = 0 To 7
            If pctTemp.Point(CurrentCol, a + Block) = vbBlack Then
               dummy = "1" & dummy
            Else
                dummy = "0" & dummy
            End If
        Next
        WalkOffset = WalkOffset + 8
        CurrentCol = CurrentCol + 1
        If CurrentCol > (txtX.Text - 1) Then
            CurrentCol = 0
            Block = Block + 8
        End If
        BinStr = BinStr & convert_dual2hex(dummy)
        dummy = ""
     Next
     txtHex.Text = BinStr
     
     UpdateBitmap
Done:
End Sub

Private Sub Command1_Click()
Dim i, k As Integer

i = 0
k = 1

txtHex.Text = ""

Do
    i = InStr(k, Text1.Text, "0x")
    If i = 0 Then
        Exit Do
    End If
    txtHex.Text = txtHex.Text & Mid(Text1.Text, i + 2, 2)
    k = i + 3
    If k >= Len(Text1.Text) Then Exit Do
Loop
txtHex.Text = UCase(txtHex.Text)
    
UpdateBitmap


End Sub

Private Sub Command2_Click()
Dim i As Integer



Text1.Text = "const unsigned char bitmap[] = {"
For i = 1 To Len(txtHex.Text) Step 2
    Text1.Text = Text1.Text & Chr(32) & "0x" & Mid(txtHex.Text, i, 2) & ","
    Next i
Text1.Text = Left(Text1.Text, Len(Text1.Text) - 1) & " };"

    
End Sub

Private Sub Command3_Click()
On Error GoTo unexpected
frmBitmap.txtHex.Text = txtHex.Text
frmBitmap.UpdateBitmap
frmBitmap.updateanigraphic txtX, 3, Text2.Text
frmBitmap.updateanigraphic txtY, 4, Text2.Text
frmBitmap.updateanigraphic txtHex.Text, 1, Text2.Text
Me.Hide
Exit Sub
unexpected:
MsgBox "A unexpected error occured", vbCritical, Me.Caption
End Sub

Private Sub Command4_Click()
Me.Hide
End Sub

Private Sub Command5_Click()
UpdateBitmap
Form1.Image1.Visible = False
Form1.picture1.Picture = frmeditBitmap.pctTemp.image
Form1.picture1.Visible = True
Form1.Show
Form1.Text1.Text = frmeditBitmap.txtHex.Text
Form1.Text4 = frmeditBitmap.txtY.Text
Form1.Text5 = frmeditBitmap.txtX.Text
Me.Hide
End Sub

Private Sub Form_Load()
txtHex.Text = "80C0701888EC3612DA6A2A2A2A2BA969C94B4B9929E3D65C444C6870E0C00000E0000000E000C02020204000E0202020200000002020E0202000E000000000E000E000C0202020400F18F0931594B6F36124B3D9C9ED687AFA9B98FFEF78ECCDE9EEA7F3DAFF7F000708080807000409090906000F0909090800000000000F0000000F010101010F000F00040909090600000001030303020201010101030E76AF5FBF7EFCFDFF7F3D1E1D0E0701C07800C02020F800C0A0A0C000E00000E000C07800F82020C000E0200000A0A0C000E800E02020C00000000000000000000000000000000000000003060707000000000000000000030000010202030001020200000003030000030000030202010003000001020203000300030000030000"
UpdateBitmap
End Sub

Private Sub pctBitmap_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim TempX As Integer
Dim TempY As Integer
    
    If Button = 1 Then
        pctBitmap.Line (CInt(X / 5 - 0.4999) * 5 + 1, CInt(Y / 5 - 0.4999) * 5 + 1)-(CInt(X / 5 + 0.5111) * 5 - 1, CInt(Y / 5 + 0.5111) * 5 - 1), vbBlack, BF
  '      pctPreview.Line ((TempX - 1) * 2, (TempY - 1) * 2)-((TempX - 1) * 2 + 1, (TempY - 1) * 2 + 1), vbBlack, BF
    ElseIf Button = 2 Then
        pctBitmap.Line (CInt(X / 5 - 0.4999) * 5 + 1, CInt(Y / 5 - 0.4999) * 5 + 1)-(CInt(X / 5 + 0.5111) * 5 - 1, CInt(Y / 5 + 0.5111) * 5 - 1), vbWhite, BF
'        pctPreview.Line ((TempX - 1) * 2, (TempY - 1) * 2)-((TempX - 1) * 2 + 1, (TempY - 1) * 2 + 1), vbWhite, BF
    End If
End Sub

Private Sub pctBitmap_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim TempX As Integer
Dim TempY As Integer

    TempX = CInt((X - 1) / 5 - 0.4999) + 1
    If TempX < 1 Then TempX = 1
    TempY = CInt((Y - 1) / 5 - 0.4999) + 1
    If TempY < 1 Then TempY = 1
    lblCoord.Caption = TempX & ", " & TempY
    
    If Button = 1 Then
        pctBitmap.Line (CInt(X / 5 - 0.4999) * 5 + 1, CInt(Y / 5 - 0.4999) * 5 + 1)-(CInt(X / 5 + 0.5111) * 5 - 1, CInt(Y / 5 + 0.5111) * 5 - 1), vbBlack, BF
'        pctPreview.Line ((TempX - 1) * 2, (TempY - 1) * 2)-((TempX - 1) * 2 + 1, (TempY - 1) * 2 + 1), vbBlack, BF
    ElseIf Button = 2 Then
        pctBitmap.Line (CInt(X / 5 - 0.4999) * 5 + 1, CInt(Y / 5 - 0.4999) * 5 + 1)-(CInt(X / 5 + 0.5111) * 5 - 1, CInt(Y / 5 + 0.5111) * 5 - 1), vbWhite, BF
'        pctPreview.Line ((TempX - 1) * 2, (TempY - 1) * 2)-((TempX - 1) * 2 + 1, (TempY - 1) * 2 + 1), vbWhite, BF
    End If
    
End Sub

Private Sub DrawBitmapPoint(X As Integer, Y As Integer, Color As Long)
    pctBitmap.Line ((X - 1) * 5 + 1, (Y - 1) * 5 + 1)-(X * 5 - 1, Y * 5 - 1), Color, BF
End Sub

Private Function ReadBitmapPoint(X As Integer, Y As Integer) As Long
    'ReadBitmapPoint = pctBitmap.Point(CInt(X / 5 - 0.4999) * 5 + 2, CInt(Y / 5 - 0.4999) * 5 + 2)
    ReadBitmapPoint = pctBitmap.Point(X * 5 + 2, Y * 5 + 2)
End Function

Private Sub ResizeBitmap(X As Integer, Y As Integer)
Dim i As Integer

    pctBitmap.Cls
    pctBitmap.Width = X * Screen.TwipsPerPixelX * 5 + Screen.TwipsPerPixelX
    pctBitmap.Height = Y * Screen.TwipsPerPixelY * 5 + Screen.TwipsPerPixelY
    pctBitmap.ScaleWidth = X * 5 + 1
    pctBitmap.ScaleHeight = Y * 5 + 1
    
    pctPreview.Height = (Y * 2 + 2) * Screen.TwipsPerPixelY
    pctPreview.Width = (X * 2 + 2) * Screen.TwipsPerPixelX

    pctBitmap.Line (0, 0)-(pctBitmap.ScaleWidth, pctBitmap.ScaleHeight), vbWhite, BF
    For i = 0 To pctBitmap.ScaleWidth Step 5
        pctBitmap.Line (i, 0)-(i, pctBitmap.ScaleHeight), vbBlack
    Next
    
    For i = 0 To pctBitmap.ScaleHeight Step 5
        pctBitmap.Line (0, i)-(pctBitmap.ScaleWidth, i), vbBlack
    Next
End Sub






Private Sub pctBitmap_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
Dim i As Integer
Dim a As Integer
Dim BinStr As String
Dim WalkOffset As Integer
Dim CurrentRow As Integer
Dim CurrentCol As Integer
Dim Block As Integer
Dim dummy As String

    WalkOffset = 1
    CurrentCol = 0
    Block = 0
    pctPreview.Cls
    For i = 1 To txtX.Text * CInt(txtY.Text / 8 + 0.49)
        For a = 0 To 7
            'Debug.Print ReadBitmapPoint(CurrentCol + 1, a + Block + 1)
            If ReadBitmapPoint(CurrentCol, a + Block) = vbBlack Then
                'pctPreview.Line (CurrentCol * 2, a * 2 + Block * 2)-(CurrentCol * 2 + 1, a * 2 + Block * 2 + 1), vbBlack, BF
                dummy = "1" & dummy
            Else
                dummy = "0" & dummy
            End If
        Next
        WalkOffset = WalkOffset + 8
        CurrentCol = CurrentCol + 1
        If CurrentCol > (CInt(txtX.Text) - 1) Then
            CurrentCol = 0
            Block = Block + 8
        End If
        BinStr = BinStr & convert_dual2hex(dummy)
        dummy = ""
     Next
     txtHex.Text = BinStr
     'Graphic_Table(comGraphic.ListIndex).hex_bitmap = txtHex.Text
     UpdateBitmap
End Sub

Private Sub scrX_DownClick()
    txtX.Text = scrX.Value
    
    UpdateBitmap
    pctBitmap_MouseUp 0, 0, 0, 0
End Sub

Private Sub scrX_UpClick()
    txtX.Text = scrX.Value
    UpdateBitmap
    pctBitmap_MouseUp 0, 0, 0, 0
End Sub

Private Sub scrY_DownClick()
    txtY.Text = scrY.Value
    UpdateBitmap
    pctBitmap_MouseUp 0, 0, 0, 0
End Sub

Private Sub scrY_UpClick()
    txtY.Text = scrY.Value
    
    UpdateBitmap
    pctBitmap_MouseUp 0, 0, 0, 0
End Sub

Private Sub txtHex_KeyUp(KeyCode As Integer, Shift As Integer)
    'Graphic_Table(comGraphic.ListIndex).hex_bitmap = txtHex.Text
    UpdateBitmap
End Sub

Private Sub txtHex_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
    UpdateBitmap
End Sub

Private Sub txtX_Change()
    If txtX.Text = "" Then Exit Sub
    scrX.Value = CInt(txtX.Text)
    UpdateBitmap
End Sub

Private Sub txtY_Change()
    If txtY.Text = "" Then Exit Sub
    scrY.Value = CInt(txtY.Text)
    UpdateBitmap
End Sub
