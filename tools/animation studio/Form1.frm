VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "BITMAP INFO"
   ClientHeight    =   3885
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   2205
   ControlBox      =   0   'False
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3885
   ScaleWidth      =   2205
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Bitmap"
      Height          =   1575
      Left            =   0
      TabIndex        =   15
      Top             =   1800
      Width           =   2175
      Begin VB.PictureBox Picture1 
         AutoSize        =   -1  'True
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         Height          =   1215
         Left            =   120
         ScaleHeight     =   1215
         ScaleWidth      =   1935
         TabIndex        =   16
         Top             =   240
         Width           =   1935
         Begin VB.Image Image1 
            Height          =   135
            Left            =   0
            Top             =   0
            Width           =   135
         End
      End
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   6480
      TabIndex        =   14
      Text            =   "Text1"
      Top             =   0
      Width           =   2895
   End
   Begin VB.TextBox Text2 
      Height          =   495
      Left            =   6480
      TabIndex        =   13
      Text            =   "Text2"
      Top             =   600
      Width           =   2895
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Check1"
      Height          =   255
      Left            =   6600
      TabIndex        =   12
      Top             =   1200
      Value           =   1  'Checked
      Width           =   2295
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   0
      TabIndex        =   11
      Top             =   3480
      Width           =   1095
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Ok"
      Height          =   375
      Left            =   1080
      TabIndex        =   10
      Top             =   3480
      Width           =   1095
   End
   Begin VB.TextBox Text3 
      Height          =   285
      Left            =   960
      TabIndex        =   4
      Text            =   "bmp00"
      Top             =   0
      Width           =   1215
   End
   Begin VB.TextBox Text4 
      Height          =   285
      Left            =   960
      TabIndex        =   3
      Text            =   "84"
      Top             =   360
      Width           =   1215
   End
   Begin VB.TextBox Text5 
      Height          =   285
      Left            =   960
      TabIndex        =   2
      Text            =   "48"
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox Text6 
      Height          =   285
      Left            =   960
      TabIndex        =   1
      Text            =   "bitmap_t"
      Top             =   1080
      Width           =   1215
   End
   Begin VB.TextBox Text7 
      Height          =   285
      Left            =   960
      TabIndex        =   0
      Text            =   "bmp_welcome"
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Bitmap:"
      Height          =   255
      Left            =   0
      TabIndex        =   9
      Top             =   0
      Width           =   735
   End
   Begin VB.Label Label3 
      Caption         =   "bitmap Y:"
      Height          =   255
      Left            =   0
      TabIndex        =   8
      Top             =   360
      Width           =   735
   End
   Begin VB.Label Label4 
      Caption         =   "Bitmap X:"
      Height          =   255
      Left            =   0
      TabIndex        =   7
      Top             =   720
      Width           =   735
   End
   Begin VB.Label Label5 
      Caption         =   "Bmp const:"
      Height          =   255
      Left            =   0
      TabIndex        =   6
      Top             =   1080
      Width           =   975
   End
   Begin VB.Label Label6 
      Caption         =   "Bmp name:"
      Height          =   255
      Left            =   0
      TabIndex        =   5
      Top             =   1440
      Width           =   855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub Command1_Click()
'On Error GoTo cancelz
Dim kez As String
'Form1.picture1 = frmBitmap.pctTemp.Picture
kez = "bmp_" & currenthold
bitmap2hexcode
Dim id As String
id = UCase(Text3.Text)

Dim name As String
name = UCase(Text7.Text)

If InStr(1, UCase(bmpidzchk), id) > 0 Then
MsgBox "please check the Bitmap id." & vbCrLf & " as the bitmap id is already in use ", vbCritical, Me.Caption
Exit Sub
End If

If InStr(1, UCase(bmpnamechk), name) > 0 Then
MsgBox "please check the Bitmap Name." & vbCrLf & " as the bitmap Name is already in use ", vbCritical, Me.Caption
Exit Sub
End If
'bmpnamechk

frmBitmap.Text3.SelText = "extern " & Text6.Text & " " & Text7.Text & ";" & vbCrLf 'bitmap_t bmp_welcome;



bitmaphex(currenthold) = Text1.Text
ccodebitmap(currenthold) = Text2.Text
ccodebmpid(currenthold) = Text3.Text
bmpidzchk = bmpidzchk & Text3.Text
ccodebmpheight(currenthold) = Text5.Text
ccodebmpwidth(currenthold) = Text4.Text
'new x,y's
ccodebmpX(currenthold) = Text4.Text
ccodebmpY(currenthold) = Text5.Text
'//
ccodebmpconstant(currenthold) = Text6.Text
ccodebmpname(currenthold) = Text7.Text
currentkez(currenthold) = kez
 bmpnamechk = bmpnamechk & Text7.Text
ccodebmpgroup = ccodebmpgroup & ccodebitmap(currenthold) & vbCrLf & vbCrLf
frmBitmap.Text2 = ccodebmpgroup
If picture1.Picture = 0 Then
Form3.picture1(currenthold + 1).Picture = Form1.Image1.Picture
Else
Form3.picture1(currenthold + 1).Picture = picture1.Picture
End If
Form3.picture1(currenthold + 1).Tag = kez
Form3.tagz(currenthold + 1).Text = kez
Form3.namez(currenthold + 1).Text = Text7.Text
currenthold = currenthold + 1

frmBitmap.TreeView1.Nodes.Add animationconst, tvwChild, kez, Text7.Text
For i% = 1 To frmBitmap.TreeView1.Nodes.count
   frmBitmap.TreeView1.Nodes(i%).Expanded = True
Next i%
previousbmpid = Text3.Text
previousbmpname = Text7.Text
frmBitmap.updateanimation
frmBitmap.Label5 = kez
Me.Hide
Exit Sub
'cancelz:
'MsgBox "Error while adding bitmap, adding of bitmap canceled", vbCritical, Left(Me.Caption, 25)
End Sub

Private Sub Command2_Click()
Me.Hide
End Sub

Public Sub bitmap2hexcode()
Text2.Text = ""
Text2.Enabled = False
Dim starthex As String
Dim count As Integer
Dim max As Integer
Dim nibble As String
Dim countt017 As Integer
Dim strhexnibble As String
Text1.Text = UCase(Text1.Text)

starthex = "0x"
count = 0
max = Len(Text1.Text)
countt017 = 1

If Check1.Value = 1 Then
Text2.SelText = "const unsigned char " & Text3.Text & "[] = {" & vbCrLf & "    "
Else
Text2.SelText = "{" & vbCrLf & "    "
End If


For count = count To max
nibble = Mid(Text1.Text, (count + 1), 2)

If Len(nibble) = 2 Then

Else
If nibble = "" Then

Else

MsgBox "Error, Hex string is not divisible by 2", vbCritical, Me.Caption
Text2.Text = ""

Exit Sub
End If
End If

If nibble = "" Then
If Check1.Value = 1 Then
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};" & vbCrLf & "const " & Text6.Text & " " & Text7.Text & " = { " & Text5.Text & ", " & Text4.Text & ", " & Text3.Text & " };"
Else
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};"
End If
Text2.Enabled = True

Exit Sub
End If

If nibble = "" Then

If Check1.Value = 1 Then
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};" & vbCrLf & "const " & Text6.Text & " " & Text7.Text & " = { " & Text5.Text & ", " & Text4.Text & ", " & Text3.Text & " };"
Else
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};"
End If
Text2.Enabled = True

Exit Sub
Else
If countt017 = 17 Then
countt017 = 0

strhexnibble = starthex & Mid(Text1.Text, (count + 1), 2) & ", " & vbCrLf & "    "
If strhexnibble = starthex & vbCrLf & "," Then

If Check1.Value = 1 Then
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};" & vbCrLf & "const " & Text6.Text & " " & Text7.Text & " = { " & Text5.Text & ", " & Text4.Text & ", " & Text3.Text & " };"
Else
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};"
End If

Text2.Enabled = True

Exit Sub
Else

Text2.SelText = strhexnibble

End If
Else

strhexnibble = starthex & Mid(Text1.Text, (count + 1), 2) & ", "

If strhexnibble = starthex & vbCrLf & "," Then

If Check1.Value = 1 Then
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};" & vbCrLf & "const " & Text6.Text & " " & Text7.Text & " = { " & Text5.Text & ", " & Text4.Text & ", " & Text3.Text & " };"
Else
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};"
End If

Text2.Enabled = True

Exit Sub
Else

Text2.SelText = strhexnibble

End If
End If
End If
'Text2.SelText = starthex & Mid(Text1.Text, (count + 1), 2) & ", "
count = count + 1
countt017 = countt017 + 1
Next
If Check1.Value = 1 Then
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};" & vbCrLf & "const " & Text6.Text & " " & Text7.Text & " = { " & Text5.Text & ", " & Text4.Text & ", " & Text3.Text & " };"
Else
Text2.Text = Left(Text2.Text, Len(Text2.Text) - 2) & vbCrLf & "};"
End If

Text2.Enabled = True
End Sub

Private Sub Form_Load()
'Form1.picture1 = frmBitmap.pctTemp.Picture
If previousbmpid = "" Then Exit Sub
Text3.Text = previousbmpid
If previousbmpname = "" Then Exit Sub
Text7.Text = previousbmpname


End Sub

Private Sub Text6_Change()
If currenthold > 0 Then
If MsgBox("Are you sure you want to change the bitmap constant?", vbYesNo, Me.Caption) = vbNo Then
Text6.Text = ccodebmpconstant(currenthold - 1)
End If
End If
End Sub

