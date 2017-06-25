Imports System
Imports System.ComponentModel
Imports System.Threading
Imports System.IO.Ports
Public Class Form1
    Public Declare Function GetAsyncKeyState Lib "user32.dll" (ByVal vKey As Int32) As UShort
    Dim myPort As Array
    Dim message As String = "Using the values on the right
you can write letters via the button on the device.
The circle is a short click, and when you hold the button
for a longer period and the sound on the buzzer changes,
it's a long click. 
You can adjust the difficulty using the potentiometer.

"
    Dim exm As String
    Private Sub ToolStripButton2_Click(sender As Object, e As EventArgs)
        ToolStripComboBox1.Items.Clear()
        myPort = IO.Ports.SerialPort.GetPortNames()
        For i = 0 To UBound(myPort)
            ToolStripComboBox1.Items.Add(myPort(i))
        Next
    End Sub
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        myPort = IO.Ports.SerialPort.GetPortNames()
        For i = 0 To UBound(myPort)
            ToolStripComboBox1.Items.Add(myPort(i))
        Next
        RichTextBox1.Font = New Font(RichTextBox1.Font.Name, CInt(ToolStripTextBox1.Text), FontStyle.Regular)
        RichTextBox1.Text = message
    End Sub

    Private Sub ToolStripButton3_Click(sender As Object, e As EventArgs) Handles ToolStripButton3.Click
        SerialPort1.Close()
        ToolStripButton3.Enabled = False
        Timer1.Stop()
        ToolStripLabel4.Text = "Not Connected"
        ToolStripComboBox1.SelectedIndex = -1
        RichTextBox1.Clear()
        RichTextBox1.Text = message
    End Sub
    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Dim receivedData As String
        receivedData = ReceiveSerialData()
        If receivedData IsNot "" Then
            RichTextBox1.Text &= receivedData
        End If
    End Sub
    Function ReceiveSerialData() As String
        Dim Incoming As String
        Try
            Incoming = SerialPort1.ReadExisting()
            If Incoming Is Nothing Then
                Return "nothing" & vbCrLf
            Else
                Return Incoming
            End If
        Catch ex As TimeoutException
            Return "Error: Serial Port read timed out."
        Catch ex As Exception
            exm = ex.Message
            Try
                SerialPort1.Close()
            Catch nmn As Exception
                exm = "USB device dissconnected"
            End Try
            ToolStripButton3.Enabled = False
            Timer1.Stop()
            ToolStripLabel4.Text = "Not connected"
            MsgBox("Disconnected." & vbCrLf & exm, MsgBoxStyle.Critical)
        End Try

    End Function

    Private Sub ToolStripTextBox1_Click(sender As Object, e As EventArgs) Handles ToolStripTextBox1.Click
        ToolStripTextBox1.SelectAll()
    End Sub

    Private Sub ToolStripButton4_Click(sender As Object, e As EventArgs) Handles ToolStripButton4.Click
        RichTextBox1.Font = New Font(RichTextBox1.Font.Name, CInt(ToolStripTextBox1.Text), FontStyle.Regular)
        If SerialPort1.IsOpen Then
            RichTextBox1.Focus()
        End If
    End Sub

    Private Sub ToolStripComboBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ToolStripComboBox1.SelectedIndexChanged
        If ToolStripComboBox1.SelectedIndex <> -1 Then
            If SerialPort1.IsOpen = True Then
                SerialPort1.Close()
            End If
            Try
                SerialPort1.PortName = ToolStripComboBox1.Text
                SerialPort1.BaudRate = 9600
                SerialPort1.Parity = IO.Ports.Parity.None
                SerialPort1.StopBits = IO.Ports.StopBits.One
                SerialPort1.DataBits = 8
                SerialPort1.Open()
                ToolStripButton3.Enabled = True
                Timer1.Start()
                ToolStripLabel4.Text = "Connected"
            Catch ex As Exception
                MsgBox("Cannot connect" & vbCrLf & ex.Message, MsgBoxStyle.Critical)
                ToolStripLabel4.Text = "Not Connected"
            End Try
            If SerialPort1.IsOpen = True Then
                RichTextBox1.Focus()
            End If
        End If
    End Sub

    Private Sub RichTextBox1_KeyDown(sender As Object, e As KeyEventArgs) Handles RichTextBox1.KeyDown
        e.SuppressKeyPress = True
        If SerialPort1.IsOpen Then
            If e.KeyCode = Keys.Delete Then
                RichTextBox1.Clear()
                RichTextBox1.Text = message
            End If
            If e.KeyValue = 8 Then
                If RichTextBox1.Text.Length > 273 Then
                    RichTextBox1.Text = RichTextBox1.Text.Remove(RichTextBox1.Text.Length - 1)
                End If
            End If
            If e.KeyCode = Keys.Enter Then
                RichTextBox1.Text += vbNewLine
            End If
            If e.KeyCode = Keys.Space Then
                RichTextBox1.Text += " "
            End If
        End If
    End Sub

    Private Sub ToolStripTextBox1_KeyDown(sender As Object, e As KeyEventArgs) Handles ToolStripTextBox1.KeyDown
        If e.KeyCode = Keys.Enter Then
            RichTextBox1.Font = New Font(RichTextBox1.Font.Name, CInt(ToolStripTextBox1.Text), FontStyle.Regular)
            If SerialPort1.IsOpen Then
                RichTextBox1.Focus()
            End If
        End If
    End Sub

    Private Sub PictureBox1_GotFocus(sender As Object, e As EventArgs) Handles PictureBox1.GotFocus
        If SerialPort1.IsOpen Then
            RichTextBox1.Focus()
        End If
    End Sub

    Private Sub Form1_GotFocus(sender As Object, e As EventArgs) Handles MyBase.GotFocus
        If SerialPort1.IsOpen Then
            RichTextBox1.Focus()
        End If
    End Sub

    Private Sub RichTextBox1_GotFocus(sender As Object, e As EventArgs) Handles RichTextBox1.GotFocus
        RichTextBox1.SelectionStart = RichTextBox1.Text.Length + 1
    End Sub

    Private Sub RichTextBox1_TextChanged(sender As Object, e As EventArgs) Handles RichTextBox1.TextChanged
        RichTextBox1.SelectionStart = RichTextBox1.Text.Length + 1
    End Sub
    Private Sub RichTextBox1_Click(sender As Object, e As EventArgs) Handles RichTextBox1.Click
        RichTextBox1.SelectionStart = RichTextBox1.Text.Length + 1
    End Sub

    Private Sub ToolStripTextBox1_KeyPress(sender As Object, e As KeyPressEventArgs) Handles ToolStripTextBox1.KeyPress
        If Asc(e.KeyChar) <> 13 AndAlso Asc(e.KeyChar) <> 8 AndAlso Not IsNumeric(e.KeyChar) Then
            e.Handled = True
        End If
    End Sub

    Private Sub ToolStripTextBox1_TextChanged(sender As Object, e As EventArgs) Handles ToolStripTextBox1.TextChanged
        If ToolStripTextBox1.Text.Length = 0 Then
            ToolStripTextBox1.Text = 0
            ToolStripTextBox1.SelectAll()
        End If
        If ToolStripTextBox1.Text > 100 Then
            ToolStripTextBox1.Text = 100
            ToolStripTextBox1.SelectionStart = ToolStripTextBox1.Text.Length + 1
        End If
    End Sub

    Private Sub ToolStripComboBox1_Click(sender As Object, e As EventArgs) Handles ToolStripComboBox1.Click
        ToolStripComboBox1.Items.Clear()
        myPort = IO.Ports.SerialPort.GetPortNames()
        For i = 0 To UBound(myPort)
            ToolStripComboBox1.Items.Add(myPort(i))
        Next
    End Sub
End Class
