String script()
{
  return "function universumChange() { document.getElementById('iframe').src = 'set?c=u'+document.getElementById('universum').value; } function ipChange() { document.getElementById('iframe').src = 'set?c=i'+document.getElementById('ip').value; } function dhcp() { document.getElementById('iframe').src = 'set?c=id'; } function etcChange() { document.getElementById('iframe').src = 'set?c=e'+document.getElementById('etc').value; } function raw() { document.getElementById('iframe').src = 'set?c=e0'; }";
}
