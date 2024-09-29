program TestIfThenElseError;

begin
  if true then
    writeln('Condition is true.');
  // Ожидается ELSE, но его нет
end.
