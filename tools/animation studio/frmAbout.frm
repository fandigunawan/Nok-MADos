VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "About . . .     "
   ClientHeight    =   6675
   ClientLeft      =   45
   ClientTop       =   345
   ClientWidth     =   4620
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Verdana"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmAbout.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6675
   ScaleWidth      =   4620
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame Frame2 
      Caption         =   "Greetz to"
      Height          =   2775
      Left            =   120
      TabIndex        =   3
      Top             =   3240
      Width           =   4455
      Begin VB.Label Label14 
         Caption         =   "and a Big thankz to JOOX"
         Height          =   255
         Left            =   1080
         TabIndex        =   16
         Top             =   1200
         Width           =   2895
      End
      Begin VB.Label Label13 
         Caption         =   "Dedicated to all [MADoS] developers ;)"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   1560
         Width           =   4215
      End
      Begin VB.Label Label12 
         Caption         =   "c0sm4ky"
         Height          =   255
         Left            =   840
         TabIndex        =   14
         Top             =   960
         Width           =   1335
      End
      Begin VB.Label Label11 
         Caption         =   "Joox"
         Height          =   255
         Left            =   960
         TabIndex        =   13
         Top             =   720
         Width           =   1095
      End
      Begin VB.Label Label10 
         Alignment       =   2  'Center
         Caption         =   "BleedR"
         Height          =   255
         Left            =   2280
         TabIndex        =   12
         Top             =   960
         Width           =   2055
      End
      Begin VB.Label Label9 
         Alignment       =   2  'Center
         Caption         =   "FLyingMatze"
         Height          =   255
         Left            =   2280
         TabIndex        =   11
         Top             =   720
         Width           =   2055
      End
      Begin VB.Label Label8 
         Alignment       =   2  'Center
         Caption         =   "and to mmt. ;D"
         Height          =   255
         Left            =   120
         TabIndex        =   10
         Top             =   2400
         Width           =   4215
      End
      Begin VB.Label Label7 
         Alignment       =   2  'Center
         Caption         =   "all members of www.GSMFreeBoard.com"
         Height          =   495
         Left            =   2160
         TabIndex        =   9
         Top             =   1920
         Width           =   2175
      End
      Begin VB.Label Label6 
         Alignment       =   2  'Center
         Caption         =   "all members of http://NokiaFree.org"
         Height          =   495
         Left            =   120
         TabIndex        =   8
         Top             =   1920
         Width           =   2130
      End
      Begin VB.Label Label5 
         Alignment       =   2  'Center
         Caption         =   "Neks"
         Height          =   255
         Left            =   2280
         TabIndex        =   7
         Top             =   480
         Width           =   2055
      End
      Begin VB.Label Label4 
         Alignment       =   2  'Center
         Caption         =   "Tnp"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   480
         Width           =   2055
      End
      Begin VB.Label Label3 
         Alignment       =   2  'Center
         Caption         =   "g3gg0"
         Height          =   255
         Left            =   2280
         TabIndex        =   5
         Top             =   240
         Width           =   2055
      End
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "NokDoc"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   240
         Width           =   2055
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1080
      TabIndex        =   2
      Top             =   6120
      Width           =   2535
   End
   Begin VB.Frame Frame1 
      Caption         =   "Info"
      Height          =   3135
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4455
      Begin VB.Label Label1 
         Alignment       =   2  'Center
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   2775
         Left            =   240
         TabIndex        =   1
         Top             =   240
         Width           =   3975
      End
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()

Unload Me
End Sub

Private Sub Form_Load()
Label1.Caption = "Nokia Animation Editor v0.1" & vbCrLf & "by Spaceimpact33" & vbCrLf & "  FLS EDIT 0.3 source code by joox " & vbCrLf & vbCrLf & "Thanks to c0sm4ky for hex to ccode and viseversa" & vbCrLf
End Sub

