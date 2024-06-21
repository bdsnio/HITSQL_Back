// 左侧按钮点击事件
document.getElementById('administratorBtn').addEventListener('click', function() {
    window.location.href = 'administrator.html';
});

document.getElementById('publishBtn').addEventListener('click', function() {
    window.location.href = 'publish.html';
});

document.getElementById('homeBtn').addEventListener('click', function() {
    window.location.href = 'home.html';
});

document.getElementById('friendBtn').addEventListener('click', function() {
    window.location.href = 'friendlist.html';
});

// 已读按钮点击事件
document.querySelectorAll('.markAsRead').forEach(function(button) {
    button.addEventListener('click', function() {
        var notification = button.closest('.notification');
        notification.classList.add('read');
    });
});

// 删除按钮点击事件
document.querySelectorAll('.delete').forEach(function(button) {
    button.addEventListener('click', function() {
        var notification = button.closest('.notification');
        notification.remove();
    });
});