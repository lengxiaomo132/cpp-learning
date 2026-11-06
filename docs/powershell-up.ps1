# ===== PowerShell profile helper: one-command upload for cpp-learning =====
# Usage:  up                 -> auto commit (timestamped message) + push
#         up "lesson13"      -> commit with custom message
function up {
    param([string]$Message)

    $repo = "C:\Users\31146\Documents\deepseek-harness\default-workspace\cpp-learning"
    if (-not (Test-Path (Join-Path $repo ".git"))) {
        Write-Host "[ERROR] repo not found: $repo" -ForegroundColor Red
        return
    }

    Push-Location $repo
    try {
        if (-not $Message) {
            $Message = "Update C++ practice " + (Get-Date -Format "yyyy-MM-dd HH:mm")
        }

        git add -A
        if ($LASTEXITCODE -ne 0) { throw "git add failed" }

        git diff --cached --quiet
        if ($LASTEXITCODE -eq 0) {
            Write-Host "No changes, pushing only..." -ForegroundColor Yellow
        }
        else {
            git commit -m $Message
            if ($LASTEXITCODE -ne 0) { throw "git commit failed" }
        }

        git push
        if ($LASTEXITCODE -ne 0) { throw "git push failed (check network / token / remote)" }

        Write-Host "[OK] Uploaded: $Message" -ForegroundColor Green
    }
    catch {
        Write-Host "[FAIL] $_" -ForegroundColor Red
    }
    finally {
        Pop-Location
    }
}
