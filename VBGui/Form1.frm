VERSION 5.00
Object = "{38E1207E-A822-4AB2-9000-3DB64ED771BB}#1.0#0"; "P2P.dll"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5325
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   5325
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command4 
      Caption         =   "Decrpyt"
      Height          =   495
      Left            =   3210
      TabIndex        =   4
      Top             =   4575
      Width           =   1230
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Encrypt"
      Height          =   570
      Left            =   1170
      TabIndex        =   3
      Top             =   4530
      Width           =   1830
   End
   Begin VB.CommandButton Command2 
      Caption         =   "LoadRemoteList"
      Height          =   480
      Left            =   780
      TabIndex        =   2
      Top             =   1635
      Width           =   3870
   End
   Begin VB.ListBox List1 
      Height          =   3960
      Left            =   120
      TabIndex        =   1
      Top             =   135
      Width           =   4395
   End
   Begin VB.CommandButton Command1 
      Caption         =   "LoadLocalList"
      Height          =   435
      Left            =   345
      TabIndex        =   0
      Top             =   1815
      Width           =   3885
   End
   Begin P2PLibCtl.Login Login 
      Left            =   135
      OleObjectBlob   =   "Form1.frx":0000
      Top             =   4800
   End
   Begin P2PLibCtl.ServerManager ServerManager1 
      Left            =   105
      OleObjectBlob   =   "Form1.frx":0024
      Top             =   4215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim sEnc As String
Private Sub Command1_Click()
    
    ServerManager1.LoadLocalServerList
End Sub

Private Sub Command2_Click()
    ServerManager1.LoadRemoteServerList
End Sub

Private Sub Command3_Click()
    sEnc = Login.EncryptString("HelloMark")
End Sub

Private Sub Command4_Click()
    Login.SetLoginInfo "", sEnc, 0, 0
End Sub

Private Sub Form_Load()
    ServerManager1.AppInitialize
End Sub

Private Sub Form_Unload(Cancel As Integer)
    ServerManager1.AppUninitialize
End Sub

Private Sub ServerManager1_OnServerAdded(ByVal Index As Long, ByVal bPermanent As Boolean)
    Dim sName As String
    Call ServerManager1.GetServer(Index, sName, 0&, 0&, 0&, 0&, 0&, bPermanent)
    List1.AddItem sName
End Sub
