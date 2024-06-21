// 按钮点击事件，跳转到个人空间
document.getElementById('myspaceBtn').addEventListener('click', function() {
    window.location.href = 'myspace.html';
});

// 绑定操作按钮的点击事件
document.querySelectorAll('.action-btn').forEach(function(button) {
    button.addEventListener('click', function() {
        var userId = this.getAttribute('data-id');
        var statusElement = document.getElementById('status-' + userId);
        
        // 切换状态显示
        var currentStatus = statusElement.textContent.trim();
        statusElement.textContent = (currentStatus === '正常') ? '禁言' : '正常';
        
        // 切换按钮文本
        this.textContent = (this.textContent === '禁言') ? '恢复' : '禁言';
    });
});