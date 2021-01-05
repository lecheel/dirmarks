# dirmarks
simple way change directory (cd) for windows 10 powershell and bash

# dirMark for PowerShell 7 Windows 10

## Added alias for PS1
```
Add following in ~\Document\PowerShell\Microsoft.PowerShell_profile.ps1
Set-Alias l list_dirmark
Set-Alias s save_dirmark

function list_dirmark
{
   $param1=$args[0]
      dirmark.exe -g $param1

      $lastcd = Get-Content -Path $HOME\\cddir -TotalCount 1
      if ($lastcd -eq "") {
         Write-Host "No ..." -ForegroundColor Yellow
      } else {
         cd $lastcd
      }
}

function save_dirmark
{
   $alias=$args[0]
      if ($alias)
      {
         dirmark.exe -s $alias
      } else {
         Write-Host "    +----- Save dirMarks -----" -ForegroundColor DarkGreen
            Write-Host "    l       - for list dirMarks"
            Write-Host "    s xxx   - Save comment for current Directory"
            Write-Host ""
      }
}


```
# dirMarks.sh for bash
```
source ~/dirMark.sh
```
![dirMarks](https://github.com/lecheel/dirmarks/blob/main/dirmark01.png)

Bonus if your are using vifm https://github.com/vifm/vifm

Added following in your vifmrc which can founded in ~\AppData\Roaming\Vifm\vifmrc
```
nnoremap <f9> :marks<cr>
nnoremap <M-q> :execute '!pwd > c:/tmp/lastdir' | quit<cr>  "Quit vifm and store last dir in c:\tmp\lastdir  
nnoremap <M-x> :quit<cr>                                    "Cancel without change current directory

#--%<-- for Microsoft.PowerShell_profile.ps1 -->%--
Set-Alias fm vimfm_wrapper
function vifm_wrapper
{
   echo "/c" > c:/tmp/lastdir
   vifm
   $str= Get-Content 'C:\tmp\lastdir' -Tail 1
   $lastxx=$str.Split("/")
   $lastdir=$str[2..$str.Length] -join ""
   $xx=$lastxx[1] +":"+ $lastdir
   Set-Location -Path $xx
}
#--%<-- for Microsoft.PowerShell_profile.ps1 -->%--
```
