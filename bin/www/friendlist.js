// 按钮点击事件，跳转到个人空间和主界面
document.getElementById('myspaceBtn').addEventListener('click', function() {
    window.location.href = 'myspace.html';
});

document.getElementById('homeBtn').addEventListener('click', function() {
    window.location.href = 'home.html';
});

// 删除好友请求
document.querySelectorAll('.delete-btn').forEach(function(button) {
    button.addEventListener('click', function() {
        // 找到按钮所在的request元素
        var request = button.parentNode;
        // 从页面中删除这个元素
        request.remove();
    });
});