# ===== 添加到 PowerShell profile：一条命令上传 cpp-learning =====
# 用法（在任意目录）：  up            -> 自动提交并推送，提交信息带时间戳
#                       up "第13课 继承"  -> 用自定义提交信息
function up {
    param([string]$Message)

    $repo = "C:\Users\31146\Documents\deepseek-harness\default-workspace\cpp-learning"
    if (-not (Test-Path (Join-Path $repo ".git"))) {
        Write-Host "找不到仓库: $repo" -ForegroundColor Red
        return
    }

    Push-Location $repo
    try {
        if (-not $Message) {
            $Message = "更新 C++ 练习 " + (Get-Date -Format "yyyy-MM-dd HH:mm")
        }

        git add -A
        if ($LASTEXITCODE -ne 0) { throw "git add 失败" }

        # 没有变更就不提交，直接推送
        git diff --cached --quiet
        if ($LASTEXITCODE -eq 0) {
            Write-Host "没有新的改动，直接推送..." -ForegroundColor Yellow
        } else {
            git commit -m $Message
            if ($LASTEXITCODE -ne 0) { throw "git commit 失败" }
        }

        git push
        if ($LASTEXITCODE -ne 0) { throw "git push 失败（检查网络 / 凭据 / remote）" }

        Write-Host "✅ 已上传: $Message" -ForegroundColor Green
    }
    catch {
        Write-Host "❌ $_" -ForegroundColor Red
    }
    finally {
        Pop-Location
    }
}
