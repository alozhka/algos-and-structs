program TestExtraElseError;

begin
  if true then
    writeln('Condition is true.')
  else
    writeln('Condition is false.');
  else
    writeln('This is an extra ELSE.');  // Лишний ELSE
end.
