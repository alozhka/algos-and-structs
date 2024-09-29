program TestExtraElseError;

begin
  if true then
    writeln('Condition is true.')
  else
    writeln('Condition is false.');   { "Здесь лишний ELSE" }
  else
    writeln('This is an extra ELSE.');
end.
