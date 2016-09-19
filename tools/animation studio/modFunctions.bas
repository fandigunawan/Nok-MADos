Attribute VB_Name = "modFunctions"
Option Explicit
Global hexstr As String
Global ccodebitmap(0 To 400) As String
Global currenthold As Single
Global ccodebmpid(0 To 400) As String
Global ccodebmpheight(0 To 400) As String
Global ccodebmpwidth(0 To 400) As String
Global ccodebmpX(0 To 400) As String
Global ccodebmpY(0 To 400) As String
Global ccodebmpconstant(0 To 400) As String
Global ccodebmpname(0 To 400) As String
Global bitmaphex(0 To 400) As String
Global animationconst As String
Global ccodebmpgroup As String
Global animationgroup As String
Global bmpidzchk As String
Global bmpnamechk As String
Global previousbmpid As String
Global previousbmpname As String
Global currentkez(0 To 400) As String
Global aniname As String
'Global animationconst As String

Function convert_hex2dec(Hex As String) As Double
    convert_hex2dec = CDbl("&H" & Hex)
End Function




Public Function convert_hex2dual(InputStr As String) As String
Dim i As Integer
Dim a As Integer
Dim dummy As String

    convert_hex2dual = ""
    For i = 1 To Len(InputStr)
        dummy = ""
        Select Case Mid(InputStr, i, 1)
            Case "0"
                convert_hex2dual = convert_hex2dual & "0000"
            Case "1"
                convert_hex2dual = convert_hex2dual & "0001"
            Case "2"
                convert_hex2dual = convert_hex2dual & "0010"
            Case "3"
                convert_hex2dual = convert_hex2dual & "0011"
            Case "4"
                convert_hex2dual = convert_hex2dual & "0100"
            Case "5"
                convert_hex2dual = convert_hex2dual & "0101"
            Case "6"
                convert_hex2dual = convert_hex2dual & "0110"
            Case "7"
                convert_hex2dual = convert_hex2dual & "0111"
            Case "8"
                convert_hex2dual = convert_hex2dual & "1000"
            Case "9"
                convert_hex2dual = convert_hex2dual & "1001"
            Case "A"
                convert_hex2dual = convert_hex2dual & "1010"
            Case "B"
                convert_hex2dual = convert_hex2dual & "1011"
            Case "C"
                convert_hex2dual = convert_hex2dual & "1100"
            Case "D"
                convert_hex2dual = convert_hex2dual & "1101"
            Case "E"
                convert_hex2dual = convert_hex2dual & "1110"
            Case "F"
                convert_hex2dual = convert_hex2dual & "1111"
        End Select
    Next
End Function

Public Function convert_dual2hex(InputStr As String) As String
Dim i As Integer
Dim a As Integer
Dim dummy As String

    convert_dual2hex = ""
    For i = 1 To Len(InputStr) Step 4
        dummy = ""
        Select Case Mid(InputStr, i, 4)
            Case "0000"
                convert_dual2hex = convert_dual2hex & "0"
            Case "0001"
                convert_dual2hex = convert_dual2hex & "1"
            Case "0010"
                convert_dual2hex = convert_dual2hex & "2"
            Case "0011"
                convert_dual2hex = convert_dual2hex & "3"
            Case "0100"
                convert_dual2hex = convert_dual2hex & "4"
            Case "0101"
                convert_dual2hex = convert_dual2hex & "5"
            Case "0110"
                convert_dual2hex = convert_dual2hex & "6"
            Case "0111"
                convert_dual2hex = convert_dual2hex & "7"
            Case "1000"
                convert_dual2hex = convert_dual2hex & "8"
            Case "1001"
                convert_dual2hex = convert_dual2hex & "9"
            Case "1010"
                convert_dual2hex = convert_dual2hex & "A"
            Case "1011"
                convert_dual2hex = convert_dual2hex & "B"
            Case "1100"
                convert_dual2hex = convert_dual2hex & "C"
            Case "1101"
                convert_dual2hex = convert_dual2hex & "D"
            Case "1110"
                convert_dual2hex = convert_dual2hex & "E"
            Case "1111"
                convert_dual2hex = convert_dual2hex & "F"
        End Select
    Next
End Function





Public Function FileExists(ByVal sFileName As String) As Boolean
'Checks if the given file exists.

Dim i As Integer
On Error Resume Next
    
    If sFileName = "" Then
        FileExists = False
        Exit Function
    End If
    i = Len(Dir$(sFileName))
    
    If err Or i = 0 Then
        FileExists = False
        Else
            FileExists = True
    End If
End Function







Public Function Reverse(Text As String) As String

Dim i As Integer
    Reverse = ""
    For i = 1 To Len(Text)
        Reverse = Mid(Text, i, 1) & Reverse
    Next
End Function




