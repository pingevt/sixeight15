
<table>
  <tr>
    <th width="100px">Node</th><th><?php print $dates; ?></th>
  </tr>
<?php
  foreach ($element['#items'] as $item) {
?>
  <tr>
    <td><?php print l($item['node']->title, 'node/' . $item['node']->nid); ?></td>
    <td><?php print $item['graph']; ?></td>
  </tr>
<?php
  }
?>
</table>
