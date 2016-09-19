VERSION 5.00
Object = "{FE0065C0-1B7B-11CF-9D53-00AA003C9CB6}#1.1#0"; "COMCT232.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmBitmap 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "[MADos] Animation Editor v1.0   by c0sm4ky & Spaceimpact33 tnx 2 Joox for FLSEdit v0.3 source"
   ClientHeight    =   7665
   ClientLeft      =   45
   ClientTop       =   660
   ClientWidth     =   10635
   Icon            =   "frmBitmap.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   7665
   ScaleWidth      =   10635
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command11 
      Caption         =   "Edit Frame"
      Enabled         =   0   'False
      Height          =   375
      Left            =   8880
      TabIndex        =   38
      Top             =   2280
      Width           =   1695
   End
   Begin VB.CommandButton cmdSaveBMP 
      Caption         =   "Save to BMP"
      Enabled         =   0   'False
      Height          =   375
      Left            =   8880
      TabIndex        =   0
      Top             =   1920
      Width           =   1695
   End
   Begin VB.CommandButton cmdInvert 
      Caption         =   "Invert"
      Enabled         =   0   'False
      Height          =   375
      Left            =   8880
      TabIndex        =   4
      Top             =   1560
      Width           =   1695
   End
   Begin VB.Frame Frame8 
      Caption         =   "C  Code header"
      Height          =   2055
      Left            =   3120
      TabIndex        =   46
      Top             =   5520
      Width           =   7455
      Begin VB.TextBox Text5 
         Height          =   375
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   51
         Top             =   1440
         Width           =   7215
      End
      Begin VB.TextBox Text3 
         Height          =   735
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   47
         Top             =   480
         Width           =   7215
      End
      Begin VB.Label Label9 
         Caption         =   "//declaration of ANIMATIONS"
         Height          =   255
         Left            =   120
         TabIndex        =   53
         Top             =   1200
         Width           =   2415
      End
      Begin VB.Label Label8 
         Caption         =   "//declaration of BITMAPS:"
         Height          =   255
         Left            =   120
         TabIndex        =   52
         Top             =   240
         Width           =   1935
      End
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "Clear"
      Enabled         =   0   'False
      Height          =   375
      Left            =   8880
      TabIndex        =   44
      Top             =   1200
      Width           =   1695
   End
   Begin VB.Frame Frame7 
      Caption         =   "Frames"
      Height          =   7575
      Left            =   0
      TabIndex        =   39
      Top             =   0
      Width           =   3015
      Begin VB.CommandButton Command5 
         Caption         =   "Delete"
         Height          =   375
         Left            =   2040
         TabIndex        =   41
         Top             =   7080
         Width           =   735
      End
      Begin VB.CommandButton cmddown 
         Caption         =   "Frame Down"
         Height          =   375
         Left            =   960
         TabIndex        =   42
         Top             =   7080
         Width           =   1095
      End
      Begin MSComctlLib.TreeView TreeView1 
         Height          =   6255
         Left            =   120
         TabIndex        =   40
         Top             =   240
         Width           =   2655
         _ExtentX        =   4683
         _ExtentY        =   11033
         _Version        =   393217
         Style           =   7
         Appearance      =   1
      End
      Begin VB.CommandButton cmdup 
         Caption         =   "Frame Up"
         Height          =   375
         Left            =   120
         TabIndex        =   43
         Top             =   7080
         Width           =   855
      End
      Begin VB.Label Label10 
         Caption         =   "To select a bitmap from tree, double click the item u would like to select."
         Height          =   375
         Left            =   120
         TabIndex        =   54
         Top             =   6600
         Width           =   2655
      End
   End
   Begin VB.PictureBox Picture2 
      Height          =   615
      Index           =   0
      Left            =   3720
      ScaleHeight     =   555
      ScaleWidth      =   1395
      TabIndex        =   37
      Top             =   8280
      Width           =   1455
   End
   Begin VB.Frame Frame6 
      Caption         =   "Player"
      Height          =   2775
      Left            =   6360
      TabIndex        =   28
      Top             =   0
      Width           =   2415
      Begin VB.Timer Timer1 
         Interval        =   100
         Left            =   120
         Top             =   240
      End
      Begin VB.CommandButton Command6 
         Caption         =   ">"
         Height          =   375
         Left            =   120
         TabIndex        =   29
         Top             =   1680
         Width           =   375
      End
      Begin VB.CommandButton Command9 
         Caption         =   "<<"
         Height          =   375
         Left            =   1800
         TabIndex        =   35
         Top             =   1680
         Width           =   495
      End
      Begin VB.CommandButton Command8 
         Caption         =   ">>"
         Height          =   375
         Left            =   1320
         TabIndex        =   34
         Top             =   1680
         Width           =   495
      End
      Begin MSComctlLib.Slider Slider1 
         Height          =   255
         Left            =   120
         TabIndex        =   32
         Top             =   2280
         Width           =   2175
         _ExtentX        =   3836
         _ExtentY        =   450
         _Version        =   393216
         LargeChange     =   100
         Min             =   100
         Max             =   1000
         SelStart        =   100
         Value           =   100
      End
      Begin VB.CommandButton Command7 
         Caption         =   "Stop"
         Height          =   375
         Left            =   480
         TabIndex        =   31
         Top             =   1680
         Width           =   855
      End
      Begin VB.PictureBox Picture1 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         Height          =   1455
         Left            =   120
         ScaleHeight     =   1455
         ScaleWidth      =   2175
         TabIndex        =   30
         Top             =   240
         Width           =   2175
         Begin VB.PictureBox player 
            AutoSize        =   -1  'True
            BackColor       =   &H00FFFFFF&
            BorderStyle     =   0  'None
            Height          =   1335
            Left            =   0
            ScaleHeight     =   1335
            ScaleWidth      =   2055
            TabIndex        =   36
            Top             =   0
            Width           =   2055
         End
      End
      Begin VB.Label Label4 
         Caption         =   "Play speed:"
         Height          =   255
         Left            =   120
         TabIndex        =   33
         Top             =   2040
         Width           =   1215
      End
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Add bmp to animation from hex"
      Enabled         =   0   'False
      Height          =   495
      Left            =   8880
      TabIndex        =   27
      Top             =   720
      Width           =   1695
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Add bmp to animation from file"
      Enabled         =   0   'False
      Height          =   495
      Left            =   8880
      TabIndex        =   26
      Top             =   240
      Width           =   1695
   End
   Begin VB.Frame Frame5 
      Caption         =   "C Code source"
      Height          =   2535
      Left            =   3120
      TabIndex        =   24
      Top             =   2880
      Width           =   7455
      Begin VB.TextBox Text4 
         Height          =   375
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   50
         Top             =   2040
         Width           =   7215
      End
      Begin VB.TextBox Text2 
         Height          =   1335
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Both
         TabIndex        =   25
         Top             =   480
         Width           =   7215
      End
      Begin VB.Label Label7 
         Caption         =   "Animations:"
         Height          =   255
         Left            =   120
         TabIndex        =   49
         Top             =   1800
         Width           =   1215
      End
      Begin VB.Label Label6 
         Caption         =   "Bitmaps:"
         Height          =   255
         Left            =   120
         TabIndex        =   48
         Top             =   240
         Width           =   1815
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "bmp2txt"
      Height          =   375
      Left            =   0
      TabIndex        =   9
      Top             =   8160
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton Command1 
      Caption         =   "txt2bmp"
      Height          =   375
      Left            =   0
      TabIndex        =   8
      Top             =   7800
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton cmdLoadBitmap 
      Caption         =   "Load from BMP"
      Height          =   375
      Left            =   1680
      TabIndex        =   1
      Top             =   8520
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Auto update Frame1"
      Height          =   375
      Left            =   480
      TabIndex        =   23
      Top             =   720
      Value           =   1  'Checked
      Width           =   1815
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   2640
      Top             =   8160
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame Frame1 
      Caption         =   "Frame1"
      Height          =   855
      Left            =   120
      TabIndex        =   18
      Top             =   1440
      Visible         =   0   'False
      Width           =   2535
      Begin VB.TextBox Text1 
         Height          =   375
         Left            =   120
         MultiLine       =   -1  'True
         TabIndex        =   19
         Top             =   240
         Width           =   2175
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Preview"
      Height          =   2775
      Left            =   3120
      TabIndex        =   16
      Top             =   0
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
         TabIndex        =   17
         Top             =   360
         Width           =   2910
      End
   End
   Begin VB.TextBox txtY 
      Height          =   330
      Left            =   720
      TabIndex        =   14
      Text            =   "28"
      Top             =   2520
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.TextBox txtX 
      Height          =   330
      Left            =   720
      TabIndex        =   11
      Text            =   "72"
      Top             =   2160
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.PictureBox pctTemp 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   735
      Left            =   5640
      ScaleHeight     =   49
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   113
      TabIndex        =   7
      Top             =   7800
      Width           =   1695
   End
   Begin VB.Frame Frame4 
      Caption         =   "Hexdata"
      Height          =   705
      Left            =   120
      TabIndex        =   5
      Top             =   360
      Visible         =   0   'False
      Width           =   2535
      Begin VB.TextBox txtHex 
         Height          =   285
         Left            =   120
         TabIndex        =   6
         Top             =   240
         Width           =   2295
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Bitmap's view"
      Height          =   480
      Left            =   240
      TabIndex        =   2
      Top             =   360
      Visible         =   0   'False
      Width           =   1485
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
   Begin ComCtl2.UpDown scrX 
      Height          =   330
      Left            =   1320
      TabIndex        =   12
      Top             =   2160
      Visible         =   0   'False
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
      Left            =   1320
      TabIndex        =   15
      Top             =   2520
      Visible         =   0   'False
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   582
      _Version        =   327681
      Value           =   28
      Max             =   65
      Min             =   1
      Enabled         =   -1  'True
   End
   Begin VB.Label Label5 
      Height          =   255
      Left            =   8520
      TabIndex        =   45
      Top             =   7440
      Width           =   1695
   End
   Begin VB.Label Label1 
      Caption         =   "Label4"
      Height          =   255
      Left            =   1920
      TabIndex        =   22
      Top             =   360
      Visible         =   0   'False
      Width           =   615
   End
   Begin VB.Label Label45 
      Caption         =   "sizeof ( bitmap ) == "
      Height          =   255
      Left            =   480
      TabIndex        =   21
      Top             =   360
      Visible         =   0   'False
      Width           =   1335
   End
   Begin VB.Label lblCoord 
      Alignment       =   2  'Center
      Height          =   255
      Left            =   -120
      TabIndex        =   20
      Top             =   360
      Visible         =   0   'False
      Width           =   2895
   End
   Begin VB.Label Label3 
      Caption         =   "Y Size:"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   2520
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label Label2 
      Caption         =   "X Size:"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   2160
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Menu mnufile 
      Caption         =   "File"
      Begin VB.Menu mnuinsbmp 
         Caption         =   "Insert BMP"
      End
      Begin VB.Menu mnubmpsave 
         Caption         =   "Save bitmap"
      End
      Begin VB.Menu mnusaveanimation 
         Caption         =   "Save Animation Sequence"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuloadanim 
         Caption         =   "Load Animation Sequence"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuexit 
         Caption         =   "Exit"
      End
   End
   Begin VB.Menu mnunew 
      Caption         =   "New"
      Begin VB.Menu mnunewani 
         Caption         =   "New animation"
      End
   End
   Begin VB.Menu mnuedit 
      Caption         =   "Edit"
      Begin VB.Menu mnueditframe 
         Caption         =   "Edit current frame"
      End
      Begin VB.Menu mniinvfra 
         Caption         =   "Invert current frame"
      End
      Begin VB.Menu mnuclrfra 
         Caption         =   "Clear current frame"
      End
   End
   Begin VB.Menu mnuinsert 
      Caption         =   "Insert"
      Begin VB.Menu mnubmpin 
         Caption         =   "Insert bmp from file"
      End
      Begin VB.Menu mnubmphexstr 
         Caption         =   "Insert bmp from hex string"
      End
      Begin VB.Menu mnucreate 
         Caption         =   "Create new bitmap"
      End
   End
   Begin VB.Menu mnuplayer 
      Caption         =   "Player"
      Begin VB.Menu mnuplay 
         Caption         =   "Play"
      End
      Begin VB.Menu mnustop 
         Caption         =   "Stop"
      End
      Begin VB.Menu mnufoward 
         Caption         =   "Forward"
      End
      Begin VB.Menu mnuback 
         Caption         =   "Back"
      End
   End
   Begin VB.Menu mnutools 
      Caption         =   "Tools"
      Begin VB.Menu mnueditbmp 
         Caption         =   "Plain Bitmap editor"
      End
   End
   Begin VB.Menu mnuhelp 
      Caption         =   "Help"
      Begin VB.Menu Mnuabout 
         Caption         =   "About"
      End
   End
End
Attribute VB_Name = "frmBitmap"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim countani As Integer



Public Sub cmdClear_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before clearing a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
Dim i As Integer
pctTemp.Cls
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
    updateanigraphic txtHex.Text, 1, Label5.Caption
End Sub

Public Sub cmdInvert_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before inverting a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
Dim i As Integer
Dim a As Integer
Dim X As Integer
Dim BinStr As String
Dim dummy As String
Dim WalkOffset As Integer
Dim CurrentRow As Integer
Dim CurrentCol As Integer
Dim Block As Integer
    pctTemp.Cls
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
    
    updateanigraphic txtHex.Text, 1, Label5.Caption
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
    Form1.picture1.Cls
    pctTemp.Width = txtX.Text * Screen.TwipsPerPixelX
    Form1.picture1.Width = txtX.Text * Screen.TwipsPerPixelX
    pctTemp.Height = txtY.Text * Screen.TwipsPerPixelY
     Form1.picture1.Height = txtY.Text * Screen.TwipsPerPixelY
    WalkOffset = 1
    CurrentCol = 0
    Block = 0
    For i = 1 To txtX.Text * CInt(txtY.Text / 8 + 0.49)
        
        dummy = Reverse(Mid(BinStr, WalkOffset, 8))
        For a = 0 To 7
            If Mid(dummy, a + 1, 1) = "1" Then
            Form1.picture1.Line (CurrentCol * 2, a * 2 + Block * 2)-(CurrentCol * 2 + 1, a * 2 + Block * 2 + 1), vbBlack, BF
                pctPreview.Line (CurrentCol * 2, a * 2 + Block * 2)-(CurrentCol * 2 + 1, a * 2 + Block * 2 + 1), vbBlack, BF
                DrawBitmapPoint CurrentCol + 1, a + Block + 1, vbBlack
                pctTemp.PSet (CurrentCol, a + Block)
                Form1.picture1.PSet (CurrentCol, a + Block)
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

Public Sub cmdSaveBMP_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before saving a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
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

Private Sub Command10_Click()
Form3.Show

End Sub

Public Sub Command11_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before editing a bitmap", vbInformation, Left(Me.Caption, 25)
mnunewani_Click
Exit Sub
End If
If Label5.Caption = "" Then
MsgBox "Please select a bitmap from the frames treeview first", vbInformation, Left(Me.Caption, 25)
mnunewani_Click
Exit Sub
End If
frmeditBitmap.Command5.Visible = False
frmeditBitmap.Command3.Visible = True
frmeditBitmap.Show
frmeditBitmap.Text2.Text = Label5.Caption
frmeditBitmap.txtHex.Text = txtHex.Text
frmeditBitmap.Command3.Visible = True
frmeditBitmap.Command4.Visible = True
frmeditBitmap.Text2.Visible = True
frmeditBitmap.Label4.Visible = True
Dim count, max As Integer
Dim image As String
count = 0
 max = currenthold + 1
 image = Label5.Caption


For count = count + 1 To max + 1
If currentkez(count - 1) = image Then

  frmeditBitmap.txtX = ccodebmpheight(count - 1)
  frmeditBitmap.txtY = ccodebmpwidth(count - 1)
   End If
  Next
  frmeditBitmap.UpdateBitmap
End Sub

Private Sub Command2_Click()
Dim i As Integer

Text1.Text = "const unsigned char bitmap[] = {"

For i = 1 To Len(txtHex.Text) Step 2
    Text1.Text = Text1.Text & Chr(32) & "0x" & Mid(txtHex.Text, i, 2) & ","
    Next i
Text1.Text = Left(Text1.Text, Len(Text1.Text) - 1) & " };"

    
End Sub

Public Sub Command3_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before inserting a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
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
     Form1.Show
Form1.Text1.Text = txtHex.Text
Form1.Text4 = txtY.Text
Form1.Text5 = txtX.Text
Form1.picture1.Visible = True
Form1.picture1 = pctTemp
     Form1.Image1.Visible = False
Done:

End Sub

Public Sub Command4_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before inserting a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
Form2.Show
Form1.Image1.Visible = True
End Sub

Private Sub Command5_Click()
TreeView1.SetFocus
If animationconst = "" Then
MsgBox "Please Create a new animation before editing a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If

If MsgBox("are you sure you want to delete " & TreeView1.SelectedItem.Text & "? ", vbYesNoCancel, Left(Me.Caption, 29)) = vbYes Then

Dim key As String

Dim kode As Integer
Dim underscore As Integer
key = TreeView1.SelectedItem.key
If TreeView1.SelectedItem.key = animationconst Then
MsgBox "please select a valid frame to delete", vbExclamation, Left(Me.Caption, 29)
Exit Sub
End If
underscore = InStr(1, TreeView1.SelectedItem.key, "_")
If underscore = 0 Then
Exit Sub
End If
kode = Mid(TreeView1.SelectedItem.key, underscore + 1, Len(TreeView1.SelectedItem.key))






bmpidzchk = Replace(bmpidzchk, ccodebmpid(kode), "")
bmpnamechk = Replace(bmpnamechk, ccodebmpname(kode), "")

bitmaphex(kode) = ""
ccodebitmap(kode) = ""
ccodebmpid(kode) = ""
ccodebmpheight(kode) = ""
ccodebmpwidth(kode) = ""
ccodebmpconstant(kode) = ""
ccodebmpname(kode) = ""
TreeView1.Nodes.Remove (TreeView1.SelectedItem.Index)
End If


Dim count As Integer
Dim max As Integer
Dim tagz As String

max = currenthold + 1
count = 0


For count = count + 1 To max + 1
tagz = Form3.picture1(count).Tag
If tagz = key Then
Dim direction As Single
direction = (count - 1)
If direction < 1 Then GoTo err



Form3.namez(count - 1).Text = ""

End If

Next
currenthold = currenthold - 1
updateanimation
err:













End Sub

Private Sub Command6_Click()
playr
End Sub
Public Sub playr()
Timer1.Enabled = True
End Sub

Private Sub Command7_Click()
Timer1.Enabled = False
End Sub

Private Sub Command8_Click()
Timer1.Enabled = False
If countani < 0 Then countani = 0
If countani >= (TreeView1.Nodes.count - 1) Then countani = 0
player.Picture = Form3.picture1(countani)

'If countani >= (TreeView1.Nodes.count - 1) Then countani = 0
countani = countani + 1
End Sub

Private Sub Command9_Click()
Timer1.Enabled = False
If countani < 0 Then countani = 0
player.Picture = Form3.picture1(countani)

If countani >= (TreeView1.Nodes.count - 1) Then countani = 0
countani = countani - 1
End Sub

Private Sub Form_Load()
'frmBitmap.Text3.Text = "//declaration of BITMAPS" & vbCrLf
txtHex.Text = "80C0701888EC3612DA6A2A2A2A2BA969C94B4B9929E3D65C444C6870E0C00000E0000000E000C02020204000E0202020200000002020E0202000E000000000E000E000C0202020400F18F0931594B6F36124B3D9C9ED687AFA9B98FFEF78ECCDE9EEA7F3DAFF7F000708080807000409090906000F0909090800000000000F0000000F010101010F000F00040909090600000001030303020201010101030E76AF5FBF7EFCFDFF7F3D1E1D0E0701C07800C02020F800C0A0A0C000E00000E000C07800F82020C000E0200000A0A0C000E800E02020C00000000000000000000000000000000000000003060707000000000000000000030000010202030001020200000003030000030000030202010003000001020203000300030000030000"
UpdateBitmap
currenthold = 0
End Sub

Private Sub Form_Terminate()
End
End Sub

Private Sub Form_Unload(Cancel As Integer)
End
End Sub

Private Sub mniinvfra_Click()
cmdInvert_Click
End Sub

Private Sub Mnuabout_Click()
frmAbout.Show
End Sub

Private Sub mnuback_Click()
Timer1.Enabled = False
If countani < 0 Then countani = 0
player.Picture = Form3.picture1(countani)

If countani >= (TreeView1.Nodes.count - 1) Then countani = 0
countani = countani - 1
End Sub

Private Sub mnubmphexstr_Click()
Command4_Click
End Sub

Private Sub mnubmpin_Click()
Command3_Click
End Sub

Private Sub mnubmpsave_Click()
cmdSaveBMP_Click
End Sub

Private Sub mnuclrfra_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before clearing a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
cmdClear_Click
End Sub

Private Sub mnucreate_Click()
frmeditBitmap.Command3.Visible = False
frmeditBitmap.Command5.Visible = True
frmeditBitmap.Show

End Sub

Private Sub mnueditbmp_Click()
frmeditBitmap.Show
frmeditBitmap.Command3.Visible = False
frmeditBitmap.Command4.Visible = False
frmeditBitmap.Text2.Visible = False
frmeditBitmap.Label4.Visible = False
End Sub

Private Sub mnueditframe_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before editing a bitmap", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
Command11_Click
End Sub

Private Sub mnuexit_Click()
End
End Sub

Private Sub mnufoward_Click()
Timer1.Enabled = False
If countani < 0 Then countani = 0
If countani >= (TreeView1.Nodes.count - 1) Then countani = 0
player.Picture = Form3.picture1(countani)

'If countani >= (TreeView1.Nodes.count - 1) Then countani = 0
countani = countani + 1
End Sub

Private Sub mnuinsbmp_Click()
Command3_Click
End Sub

Public Sub mnunewani_Click()
On Error GoTo err:
Text5.Text = ""
currenthold = 0
aniname = InputBox("Please enter Name of new animation", Left(Me.Caption, 29))



check:
If aniname = "" Then
If MsgBox("Please enter a valid Name for new animation", vbRetryCancel, Left(Me.Caption, 29)) = vbCancel Then Exit Sub
aniname = InputBox("Please enter a valid Name for new animation", Left(Me.Caption, 29))
GoTo check
Else: GoTo ok
End If
ok:
animationconst = (InputBox("Please enter Constant of new animation", Left(Me.Caption, 29)))
chek2:
If animationconst = "" Then
If MsgBox("Please enter a valid Constant for new animation", vbRetryCancel, Left(Me.Caption, 29)) = vbCancel Then Exit Sub
animationconst = (InputBox("Please enter a valid Constant for new animation", Left(Me.Caption, 29)))
GoTo chek2
Else: GoTo ok2
End If
ok2:



TreeView1.Nodes.Clear
TreeView1.Nodes.Add , , animationconst, aniname
For currenthold = currenthold To 400
bitmaphex(currenthold) = ""
ccodebitmap(currenthold) = ""
ccodebmpid(currenthold) = ""
ccodebmpheight(currenthold) = ""
ccodebmpwidth(currenthold) = ""
ccodebmpconstant(currenthold) = ""
ccodebmpname(currenthold) = ""

'Form3.namez(currenthold).Text = ""
currenthold = currenthold + 1

Next

currenthold = 0
For currenthold = currenthold To 41
Form3.namez(currenthold).Text = ""
Next
Command3.Enabled = True
Command4.Enabled = True
Command11.Enabled = True
cmdClear.Enabled = True
cmdInvert.Enabled = True
cmdSaveBMP.Enabled = True
Text2 = ""
Text3 = ""
Text4 = ""
txtHex.Text = "80C0701888EC3612DA6A2A2A2A2BA969C94B4B9929E3D65C444C6870E0C00000E0000000E000C02020204000E0202020200000002020E0202000E000000000E000E000C0202020400F18F0931594B6F36124B3D9C9ED687AFA9B98FFEF78ECCDE9EEA7F3DAFF7F000708080807000409090906000F0909090800000000000F0000000F010101010F000F00040909090600000001030303020201010101030E76AF5FBF7EFCFDFF7F3D1E1D0E0701C07800C02020F800C0A0A0C000E00000E000C07800F82020C000E0200000A0A0C000E800E02020C00000000000000000000000000000000000000003060707000000000000000000030000010202030001020200000003030000030000030202010003000001020203000300030000030000"
UpdateBitmap
currenthold = 0
currenthold = 0
  frmeditBitmap.txtX = "72"
  frmeditBitmap.txtY = "28"
Text5.Text = "extern " & animationconst & " " & aniname & ";" 'ani_t ani_01;"
Exit Sub
err:
MsgBox "Error while starting new animation. please try again", vbExclamation, Left(Me.Caption, 29)
End Sub

Private Sub mnuplay_Click()
playr
End Sub

Private Sub mnustop_Click()
Timer1.Enabled = False
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

Private Sub pctPreview_Click()
Command11_Click
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

Private Sub Timer1_Timer()
Timer1.Interval = Slider1.Value
If countani < 0 Then countani = 0
player.Picture = Form3.picture1(countani)

If countani >= (TreeView1.Nodes.count - 1) Then countani = 0
countani = countani + 1
End Sub

Public Sub TreeView1_DblClick()
On Error GoTo err
Dim kode As Integer
Dim underscore As Integer
If TreeView1.SelectedItem.key = animationconst Then Exit Sub
underscore = InStr(1, TreeView1.SelectedItem.key, "_")
If underscore = 0 Then Exit Sub
kode = Mid(TreeView1.SelectedItem.key, underscore + 1, Len(TreeView1.SelectedItem.key))
txtHex = bitmaphex(kode)
txtX = ccodebmpheight(kode)
txtY = ccodebmpwidth(kode)
pctTemp.Picture = Picture2(0).Picture


Label5.Caption = TreeView1.SelectedItem.key
UpdateBitmap
err:
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
Private Sub cmdDown_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before moving a frame", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
TreeView1.SetFocus
  MoveNode TreeView1, TreeView1.SelectedItem, "DOWN"
End Sub

Private Sub cmdUP_Click()
If animationconst = "" Then
MsgBox "Please Create a new animation before moving a frame", vbInformation, Left(Me.Caption, 29)
mnunewani_Click
Exit Sub
End If
TreeView1.SetFocus
  MoveNode TreeView1, TreeView1.SelectedItem, "UP"
End Sub



'This is our recursive function to find the children
'Of a node, and that' nodes children, and so on.
Private Sub GetChildren(tvw As TreeView, nodN As Node, nodP As Node)
Dim nodC As Node, nodT As Node
Dim i As Integer

  With tvw
    'For each children in the tree
    For i = 1 To nodN.Children
      'If it's the first child:
      If i = 1 Then
        'Add the node:
        Set nodC = .Nodes.Add(nodP.Index, tvwChild, , nodN.Child.Text)
        'Set us up for the next child:
        Set nodT = nodN.Child.Next
        'Get the added nodes children:
        If nodN.Child.Children <> 0 Then
          GetChildren tvw, nodN.Child, nodC
        End If
      'It's not the first child:
      Else
        On Error Resume Next
        'Add the node:
        Set nodC = .Nodes.Add(nodP.Index, tvwChild, , nodT.Text)
        'Get the added nodes children:
        If nodT.Children <> 0 Then
          GetChildren tvw, nodT, nodC
        End If
        'Set us up again:
        Set nodT = nodT.Next
      End If
    Next
  End With
End Sub

Private Sub MoveNode(tvw As TreeView, nodX As Node, direction As String)
Dim nodN As Node
Dim strKey As String
  
  'All we do here is copy the node and set it as the previous
  'Nodes previous node. A little confusing, but it works.
  'We then add all the children and delete the original
  'Node
  
  With tvw
    Select Case direction
      Case "UP"
        If Not nodX.Previous Is Nothing Then
        moveimgup tvw.SelectedItem.key
          Set nodN = .Nodes.Add(nodX.Previous, tvwPrevious, , nodX.Text)
          
        Else
          Exit Sub
        End If
      Case "DOWN"
        If Not nodX.Next Is Nothing Then
        moveimgdown tvw.SelectedItem.key
          Set nodN = .Nodes.Add(nodX.Next, tvwNext, , nodX.Text)
        Else
          Exit Sub
        End If
    End Select
      
    nodN.Selected = True
      
    If nodX.Children <> 0 Then
      GetChildren tvw, nodX, nodN
    End If
      
    strKey = nodX.key
    .Nodes.Remove nodX.Index
    Set nodX = Nothing
    nodN.key = strKey
  End With
End Sub

Public Function moveimgup(key As String)
Dim count As Integer
Dim max As Integer
Dim tagz As String
max = currenthold + 1
count = 0

For count = count + 1 To max
tagz = Form3.picture1(count).Tag
If tagz = key Then
Dim direction As Single
direction = (count - 1)
If direction < 1 Then GoTo err

Form3.buffer.Picture = Form3.picture1(count).Picture

Form3.buffer.Tag = Form3.picture1(count).Tag
Form3.buffernamz.Text = Form3.namez(count).Text
Form3.buffertag.Text = Form3.tagz(count).Text

Form3.picture1(count).Picture = Form3.picture1(direction).Picture

Form3.tagz(count).Text = Form3.tagz(direction).Text
Form3.namez(count).Text = Form3.namez(direction).Text
Form3.picture1(count).Tag = Form3.picture1(direction).Tag


Form3.picture1(direction).Picture = Form3.buffer.Picture


Form3.picture1(direction).Tag = Form3.buffer.Tag
Form3.tagz(direction).Text = Form3.buffertag.Text
Form3.namez(direction).Text = Form3.buffernamz.Text
End If
Form3.buffer.Cls

Next
updateanimation
err:
End Function
Public Function moveimgdown(key As String)
Dim count As Integer
Dim max As Integer
Dim tagz As String
max = currenthold + 1
count = 0

For count = count + 1 To max
tagz = Form3.picture1(count).Tag
If tagz = key Then
Dim direction As Single
direction = (count + 1)
If direction < 1 Then GoTo err
If direction > currenthold Then GoTo err

Form3.buffer.Picture = Form3.picture1(count).Picture

Form3.buffer.Tag = Form3.picture1(count).Tag
Form3.buffernamz.Text = Form3.namez(count).Text
Form3.buffertag.Text = Form3.tagz(count).Text

Form3.picture1(count).Picture = Form3.picture1(direction).Picture

Form3.tagz(count).Text = Form3.tagz(direction).Text
Form3.namez(count).Text = Form3.namez(direction).Text
Form3.picture1(count).Tag = Form3.picture1(direction).Tag


Form3.picture1(direction).Picture = Form3.buffer.Picture


Form3.picture1(direction).Tag = Form3.buffer.Tag
Form3.tagz(direction).Text = Form3.buffertag.Text
Form3.namez(direction).Text = Form3.buffernamz.Text
End If
Form3.buffer.Cls

Next

err:
updateanimation


End Function

Public Sub updateanigraphic(Datain As String, changeinfo As Integer, image As String)
'for changeinfo =
'1 as bitmaphex(0 To 400) As String

'2 as ccodebmpid(0 To 400) As String
'3 as ccodebmpheight(0 To 400) As String
'4 as ccodebmpwidth(0 To 400) As String
'5 as ccodebmpconstant(0 To 400) As String
'6 as ccodebmpname(0 To 400) As String
 Dim max, count As Integer

 max = currenthold + 1

 count = 0
  
Select Case changeinfo
Case 1

GoTo updatebmp

Case 2
GoTo updateid

Case 3
GoTo updateheight
  
Case 4
GoTo updatewidth
 
Case 5
GoTo updatebmpconst
 
Case 6
GoTo updatebmpname
End Select
Exit Sub

updatebmp:
For count = count + 1 To max + 1
  If currentkez(count - 1) = image Then
  ' MsgBox bitmaphex(count)
  bitmaphex(count - 1) = Datain
 
  ccodebitmap(count - 1) = bitmap2hexcode(Datain, ccodebmpid(count - 1), ccodebmpwidth(count - 1), _
  ccodebmpheight(count - 1), ccodebmpconstant(count - 1), ccodebmpname(count - 1))
   Dim maxz As Integer
  Dim countz As Integer
  countz = 0
   maxz = currenthold + 1
  
  For countz = countz + 1 To maxz + 1
  Dim tagz As String
  tagz = Form3.tagz(countz).Text
  'MsgBox tagz
  If tagz = image Then
  Form3.picture1(countz).Picture = pctTemp.image
  End If
  ''countz = countz + 1
  Next
  
  
  
 '  MsgBox bitmaphex(count)
  End If
 
  'count = count + 1
Next count
Exit Sub

updateid:
For count = count + 1 To max + 1
  If currentkez(count - 1) = image Then
  ccodebmpid(count - 1) = Datain
  End If

  Next
Exit Sub

updateheight:
For count = count + 1 To max + 1
If currentkez(count - 1) = image Then ccodebmpheight(count - 1) = Datain
  
  Next
  Exit Sub
  
updatewidth:
For count = count + 1 To max + 1
 If currentkez(count - 1) = image Then
  ccodebmpwidth(count - 1) = Datain
   End If

  Next
  Exit Sub
  
updatebmpconst:
For count = count + 1 To max + 1
 If currentkez(count - 1) = image Then
  ccodebmpconstant(count - 1) = Datain
  End If
  Next
  Exit Sub
  
updatebmpname:
For count = count + 1 To max + 1
  If currentkez(count - 1) = image Then
  ccodebmpname(count - 1) = Datain
  End If
  Next
  Exit Sub


End Sub
Public Function bitmap2hexcode(hexin As String, txtt3 As String, txtt4 As String, txtt5 As String _
, txtt6 As String, txtt7 As String) As String
bitmap2hexcode = ""
'
Dim starthex As String
Dim count As Integer
Dim max As Integer
Dim nibble As String
Dim countt017 As Integer
Dim strhexnibble As String
hexin = UCase(hexin)

starthex = "0x"
count = 0
max = Len(hexin)
countt017 = 1

If Check1.Value = 1 Then
bitmap2hexcode = bitmap2hexcode & "const unsigned char " & txtt3 & "[] = {" & vbCrLf & "    "
Else
bitmap2hexcode = bitmap2hexcode & "{" & vbCrLf & "    "
End If


For count = count To max
nibble = Mid(hexin, (count + 1), 2)

If Len(nibble) = 2 Then

Else
If nibble = "" Then

Else

MsgBox "Error, Hex string is not divisible by 2", vbCritical, Left(Me.Caption, 29)
bitmap2hexcode = ""

Exit Function
End If
End If

If nibble = "" Then
If Check1.Value = 1 Then
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt5 & ", " & txtt4 & ", " & txtt3 & " };"
Else
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};"
End If
'

Exit Function
End If

If nibble = "" Then

If Check1.Value = 1 Then
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt5 & ", " & txtt4 & ", " & txtt3 & " };"
Else
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};"
End If


Exit Function
Else
If countt017 = 17 Then
countt017 = 0

strhexnibble = starthex & Mid(hexin, (count + 1), 2) & ", " & vbCrLf & "    "
If strhexnibble = starthex & vbCrLf & "," Then

If Check1.Value = 1 Then
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt5 & ", " & txtt4 & ", " & txtt3 & " };"
Else
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};"
End If



Exit Function
Else

bitmap2hexcode = bitmap2hexcode & strhexnibble

End If
Else

strhexnibble = starthex & Mid(hexin, (count + 1), 2) & ", "

If strhexnibble = starthex & vbCrLf & "," Then

If Check1.Value = 1 Then
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt5 & ", " & txtt4 & ", " & txtt3 & " };"
Else
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};"
End If



Exit Function
Else

bitmap2hexcode = bitmap2hexcode & strhexnibble

End If
End If
End If
'bitmap2hexcode = bitmap2hexcode & starthex & Mid(hexin, (count + 1), 2) & ", "
count = count + 1
countt017 = countt017 + 1
Next
If Check1.Value = 1 Then
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt5 & ", " & txtt4 & ", " & txtt3 & " };"
Else
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};"
End If


End Function
Public Sub updateanimation()
Text4.Text = ""

Dim animationtable As String
Dim bmptable As String
Dim count, max As Integer

Dim count2, max2 As Integer
 max = currenthold

 count = 0
  max2 = currenthold

 count2 = 0
 animationtable = "const " & animationconst & " " & aniname & "[] = { "
For count = count + 1 To max

animationtable = animationtable & "&" & Form3.namez(count).Text & ", "

' Form3.namez (count)

Next

 animationtable = animationtable & " NULL };"
 Text4.Text = animationtable
End Sub
Public Function getbmpname(bmpid As String) As String
Dim count2, max2 As Integer

  max2 = currenthold + 1

 count2 = 0
For count2 = count2 To max2
If bmpid = currentkez(count2) Then
getbmpname = ccodebmpname(count2)
End If
count2 = count2 + 1
Next
End Function

