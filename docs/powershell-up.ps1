# ===== PowerShell profile helper: one-command upload for cpp-learning =====
# Usage:  up                 -> auto commit (timestamped message) + push
#         up "lesson13"      -> commit with custom message
# Behavior when there are no file changes:
#   - with a custom message  -> creates an empty commit so the note is kept
#   - without a message      -> does NOT create an empty commit, prints a notice
function up {
    param([string]$Message)

    $repo = "C:\Users\31146\Documents\deepseek-harness\default-workspace\cpp-learning"
    if (-not (Test-Path (Join-Path $repo ".git"))) {
        Write-Host "[ERROR] repo not found: $repo" -ForegroundColor Red
        return
    }

    $hasCustomMessage = [bool]$Message

    Push-Location $repo
    try {
        if (-not $Message) {
            $Message = "Update C++ practice " + (Get-Date -Format "yyyy-MM-dd HH:mm")
        }

        git add -A
        if ($LASTEXITCODE -ne 0) { throw "git add failed" }

        git diff --cached --quiet
        if ($LASTEXITCODE -eq 0) {
            # No file changes staged
            if ($hasCustomMessage) {
                Write-Host "No file changes, recording note as empty commit..." -ForegroundColor Yellow
                git commit --allow-empty -m $Message
                if ($LASTEXITCODE -ne 0) { throw "git commit --allow-empty failed" }
            }
            else {
                Write-Host "[NOTE] No file changes - nothing to commit." -ForegroundColor Yellow
                Write-Host "       Your note was NOT recorded. Nothing to upload." -ForegroundColor Yellow
                Write-Host "       (Tip: use  up ""your note""  to record a note without file changes.)" -ForegroundColor DarkGray
                return
            }
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
