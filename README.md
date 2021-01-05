# dirmarks
simple way change directory (cd) for windows 10 powershell and bash

# dirMark for PowerShell 7 Windows 10

## Added alias for PS1
```
Add following in ~\Document\PowerShell\Microsoft.PowerShell_profile.ps1
Set-Alias l list_dirmark
Set-Alias l list_dirmark

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
