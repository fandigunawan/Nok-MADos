VERSION 5.00
Begin VB.Form Form4 
   Caption         =   "Form4"
   ClientHeight    =   0
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   1725
   Icon            =   "Form4.frx":0000
   LinkTopic       =   "Form4"
   ScaleHeight     =   0
   ScaleWidth      =   1725
   StartUpPosition =   3  'Windows Default
End
Attribute VB_Name = "Form4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
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

MsgBox "Error, Hex string is not divisible by 2", vbCritical, Me.Caption
bitmap2hexcode = ""

Exit Function
End If
End If

If nibble = "" Then
If Check1.Value = 1 Then
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt4 & ", " & txtt5 & ", " & txtt3 & " };"
Else
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};"
End If
'

Exit Function
End If

If nibble = "" Then

If Check1.Value = 1 Then
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt4 & ", " & txtt5 & ", " & txtt3 & " };"
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
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt4 & ", " & txtt5 & ", " & txtt3 & " };"
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
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt4 & ", " & txtt5 & ", " & txtt3 & " };"
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
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};" & vbCrLf & "const " & txtt6 & " " & txtt7 & " = { " & txtt4 & ", " & txtt5 & ", " & txtt3 & " };"
Else
bitmap2hexcode = Left(bitmap2hexcode, Len(bitmap2hexcode) - 2) & vbCrLf & "};"
End If


End Function

