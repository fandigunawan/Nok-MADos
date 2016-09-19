VERSION 5.00
Begin VB.Form Form2 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Enter hex code"
   ClientHeight    =   1575
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4920
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   Icon            =   "Form2.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1575
   ScaleWidth      =   4920
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   6
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      Height          =   285
      Left            =   1680
      TabIndex        =   5
      Text            =   "84"
      Top             =   1200
      Width           =   615
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   600
      TabIndex        =   3
      Text            =   "48"
      Top             =   1200
      Width           =   495
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Use this Code"
      Height          =   375
      Left            =   2400
      TabIndex        =   1
      Top             =   1200
      Width           =   1335
   End
   Begin VB.TextBox Text1 
      Height          =   1095
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4935
   End
   Begin VB.Label Label2 
      Caption         =   "    X:"
      Height          =   255
      Left            =   1200
      TabIndex        =   4
      Top             =   1200
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "       Y:"
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   1200
      Width           =   735
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
frmBitmap.txtHex = Text1.Text
frmBitmap.txtY.Text = Text2.Text
 frmBitmap.txtX.Text = Text3.Text
frmBitmap.UpdateBitmap
Form1.Image1.Picture = frmBitmap.pctTemp.image

Form1.Show
Form1.Text1.Text = frmBitmap.txtHex.Text
Form1.Text4 = frmBitmap.txtY.Text
Form1.Text5 = frmBitmap.txtX.Text
Text1.Text = ""
'Form1.picture1 = frmBitmap.pctTemp.Picture
Me.Hide
End Sub

Private Sub Command2_Click()
Me.Hide
End Sub
