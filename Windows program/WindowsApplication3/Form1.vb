Public Class Form1
    Dim myPort As Array
    Dim msg_en As String = "Using the values on the right you can write letters and numbers via the button on the device.
The circle is a short click and when you hold the button for a longer period and the sound on the buzzer changes, it's a long click (dash). 
You can adjust the difficulty using the potentiometer.

"
    Dim msg_srb As String = "Koristeći vrednosti na desnoj strani ekrana možete napisati slova i brojeve pomoću prekidača na uređaju. 
Krug je kratak klik, a kada držite prekidač duže vreme i čujete da se zvuk na uređaju promenio, to je dug klik (crta).
Možete podesiti težinu koristeći potenciometar.

"
    Dim dscnt_srb As String = "Otkači se"
    Dim usetxt_srb As String = "Koristi tekst"
    Dim fontlbl_srb As String = "Veličina fonta"
    Dim setbnt_srb As String = "Podesi"
    Dim langlbl_srb As String = "Jezik"
    Dim connlbl_nc_srb As String = "Nije zakačen"
    Dim connlbl_no_srb As String = "Zakačen"
    Dim form_srb As String = "Morze kod"
    Dim dscnt_en As String = "Dissconnect"
    Dim fontlbl_en As String = "Font size"
    Dim setbnt_en As String = "Set"
    Dim langlbl_en As String = "Laguage"
    Dim connlbl_nc_en As String = "Not connected"
    Dim connlbl_no_en As String = "Connected"
    Dim usetxt_en As String = "Use text"
    Dim form_en As String = "Morse code"
    Dim connlbl_no_txt As String
    Dim connlbl_nc_txt As String
    Dim message As String
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
        If usetxt.Checked Then RichTextBox1.Text = message
        ToolStripComboBox2.Items.Add("Srpski")
        ToolStripComboBox2.Items.Add("English")
        ToolStripComboBox2.SelectedIndex = 0
        connlbl_nc_txt = connlbl_nc_srb
        connlbl_no_txt = connlbl_no_srb
        message = msg_srb
        RichTextBox1.ContextMenuStrip = ContextMenuStrip1
        usetxt.Checked = True
        RichTextBox1.Text = message
    End Sub

    Private Sub dscnt_Click(sender As Object, e As EventArgs) Handles dscnt.Click
        SerialPort1.Close()
        dscnt.Enabled = False
        Timer1.Stop()
        connlbl.Text = connlbl_nc_txt
        ToolStripComboBox1.SelectedIndex = -1
        RichTextBox1.Clear()
        If usetxt.Checked Then RichTextBox1.Text = message
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
            dscnt.Enabled = False
            Timer1.Stop()
            connlbl.Text = connlbl_nc_txt
            MsgBox(exm, MsgBoxStyle.Critical)
        End Try

    End Function

    Private Sub ToolStripTextBox1_Click(sender As Object, e As EventArgs) Handles ToolStripTextBox1.Click
        ToolStripTextBox1.SelectAll()
    End Sub

    Private Sub ToolStripButton4_Click(sender As Object, e As EventArgs) Handles setbtn.Click
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
                dscnt.Enabled = True
                Timer1.Start()
                connlbl.Text = connlbl_no_txt
                If usetxt.Checked Then RichTextBox1.Text = message
            Catch ex As Exception
                MsgBox(ex.Message, MsgBoxStyle.Critical, "Cannot connect")
                connlbl.Text = connlbl_nc_txt
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
                If usetxt.Checked Then RichTextBox1.Text = message
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
    Private Sub ToolStripComboBox2_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ToolStripComboBox2.SelectedIndexChanged
        If ToolStripComboBox2.SelectedIndex = 0 Then
            dscnt.Text = dscnt_srb
            fontlbl.Text = fontlbl_srb
            setbtn.Text = setbnt_srb
            langlbl.Text = langlbl_srb
            connlbl_nc_txt = connlbl_nc_srb
            connlbl_no_txt = connlbl_no_srb
            message = msg_srb
            Me.Text = form_srb
            PictureBox1.Image = My.Resources.morse_srb
            usetxt.Text = usetxt_srb
        Else
            dscnt.Text = dscnt_en
            fontlbl.Text = fontlbl_en
            setbtn.Text = setbnt_en
            langlbl.Text = langlbl_en
            connlbl_nc_txt = connlbl_nc_en
            connlbl_no_txt = connlbl_no_en
            message = msg_en
            Me.Text = form_en
            PictureBox1.Image = My.Resources.morse_en
            usetxt.Text = usetxt_en
        End If
        If SerialPort1.IsOpen Then
            connlbl.Text = connlbl_no_txt
        Else
            connlbl.Text = connlbl_nc_txt
        End If
        If usetxt.Checked Then RichTextBox1.Text = message
    End Sub

    Private Sub usetxt_Click(sender As Object, e As EventArgs) Handles usetxt.Click
        If Not usetxt.Checked Then
            RichTextBox1.Clear()
        Else
            RichTextBox1.Text = message
        End If
    End Sub

    Private Sub cpy_Click(sender As Object, e As EventArgs)
        RichTextBox1.Copy()
    End Sub
End Class
