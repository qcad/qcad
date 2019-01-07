/**
 * Simple Input API.
 */

/**
 * Display an input dialog box and return an integer.
 * \ingroup ecma_simple
 *
 * \param title - Title of dialog box 
 * \param prompt - Prompt to display.
 * \param value - Value to display in the input box (Default = 0).
 * \param step - Spin box step value (Default = 1).
 * \param lower - minimum value (Default = -2147483647)
 * \param upper - maximum value (Default = 2147483647)
 */
function getInt(title, prompt, value, step, lower, upper) {
    var dialog = new QInputDialog();
    dialog.setInputMode(QInputDialog.IntInput);
    dialog.setWindowTitle(title);
    dialog.setLabelText(prompt);
	if (isNull(value)) value = 0;
    dialog.setIntValue(value);
	if (isNull(step)) step = 1;
    dialog.setIntStep(step);
	if (isNull(upper)) upper = 2147483647;
    dialog.setIntMaximum(upper);
	if (isNull(lower)) lower = -2147483647;
    dialog.setIntMinimum(lower);

    if (!dialog.exec()) {
        dialog.destroy();
	}
    return dialog.intValue();
}

/**
 * Display an input dialog box and return a double.
 * \ingroup ecma_simple
 *
 * \param title - Title of dialog box 
 * \param prompt - Prompt to display.
 * \param value - Value to display in the input box (Default = 0.0).
 * \param prec - Spin button precision (Default = 1).
 * \param lower - minimum value (Default = -2147483647)
 * \param upper - maximum value (Default = 2147483647)
 */
function getDouble(title, prompt, value, prec, lower, upper) {
    var dialog = new QInputDialog();
    dialog.setInputMode(QInputDialog.DoubleInput);
    dialog.setWindowTitle(title);
    dialog.setLabelText(prompt);
	if (isNull(value)) value = 0.0;
    dialog.setDoubleValue(value);
	if (isNull(prec)) prec = 1;
    dialog.setDoubleDecimals(prec);
	if (isNull(upper)) upper = 2147483647;
    dialog.setDoubleMaximum(upper);
	if (isNull(lower)) lower = -2147483647;
    dialog.setDoubleMinimum(lower);

    if (!dialog.exec()) {
        dialog.destroy();
	}
    return dialog.doubleValue();
}

/**
 * Display an input dialog box and return string.
 * \ingroup ecma_simple
 *
 * \param title - Title of dialog box 
 * \param prompt - Prompt to display.
 * \param txt - Text to display in the input box.
 */
function getText(title, prompt, txt) {
    var dialog = new QInputDialog();
    dialog.setInputMode(QInputDialog.TextInput);
    dialog.setWindowTitle(title);
    dialog.setLabelText(prompt);
	if (isNull(txt)) txt = "";
    dialog.setTextValue(txt);

    if (!dialog.exec()) {
        dialog.destroy();
	}
    return dialog.textValue();
}

/**
 * Display a combo drop down box and return item.
 * \ingroup ecma_simple
 *
 * \param title - Title of dialog box 
 * \param prompt - Prompt to display.
 * \param items - List of items to display in the combo box.
 * \param idx - index of item to display (Default = 0)
 * \param splitStr - Character or string to split the items (Default = ",")
 */
function getItem(title, prompt, items, idx, splitStr) {
    var dialog = new QInputDialog();
    dialog.setInputMode(3);
    dialog.setWindowTitle(title);
    dialog.setLabelText(prompt);
	if (isNull(splitStr)) splitStr = ",";
	var itemlst = items.split(splitStr);
    dialog.setComboBoxItems(itemlst);
	if (isNull(idx)) idx = 0;
    var children = dialog.children();
	for (var i = 0; i < children.length; i++) {
		var c = children[i];
		if (isComboBox(c)) {
			c.setCurrentIndex(idx);
			break;
		}
	}

    if (!dialog.exec()) {
        dialog.destroy();
	}
    var txt = dialog.textValue();
	//var idx = itemlst.indexOf(txt, 0);
	return txt;
}


