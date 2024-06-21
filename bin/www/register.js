document.getElementById('registrationForm').addEventListener('submit', function(event) {
    event.preventDefault(); // 阻止表单的默认提交行为

    // 获取两次密码输入的值
    var password = document.getElementById('password').value;
    var confirmPassword = document.getElementById('confirmPassword').value;

    // 检查两次输入的密码是否一致
    if (password === confirmPassword) {
        // 假设用户名输入字段的id为"username"
        var username = document.getElementById('username').value;
        // 存储用户名到localStorage
        localStorage.setItem('username', username); 
        // 如果一致，跳转到home.html
        window.location.href = 'home.html';
    } else {
        // 如果不一致，警告用户并阻止表单提交
        alert('两次输入的密码不一致，请重新输入！');
        // 清空密码字段，允许用户重新输入
        document.getElementById('confirmPassword').value = '';
        // 聚焦到确认密码输入框，方便用户直接修改
        document.getElementById('confirmPassword').focus();
    }
});